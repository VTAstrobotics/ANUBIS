#pragma once

#include "motor_control/motor_controller_base.hpp"
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <string>
#include <cmath>
#include <functional>
#include <chrono>

namespace motor_control {

/**
 * SimMotorController — Kraken X44 second-order electromechanical model
 *
 * Models the coupled electrical + mechanical dynamics of the X44:
 *
 *   Electrical:   L·(di/dt) = V_app - R·i - Ke·ω
 *   Mechanical:   J·(dω/dt) = Kt·i  - b·ω
 *   Kinematic:    dθ/dt     = ω
 *
 * Parameters derived from WCP official datasheet (trapezoidal commutation):
 *   Free Speed    7530 RPM  |  Free Current   1.4 A
 *   Stall Torque  4.05 N·m  |  Stall Current  275 A
 *   KT            14.81 mN·m/A  |  Peak Power  823 W
 *
 * ROS2 Parameters (set via launch file or ros2 param):
 *   ~joint_name      (string)  – must match URDF joint name
 *   ~gear_ratio      (double)  – motor→joint ratio   (default 1.0)
 *   ~bus_voltage     (double)  – supply voltage [V]   (default 14.8)
 *   ~current_limit   (double)  – stator current cap [A] (default 80.0)
 *   ~load_inertia    (double)  – reflected load inertia [kg·m²] (default 0.0)
 */
class SimMotorController : public MotorControllerBase
{
public:
  SimMotorController()
  : MotorControllerBase()
  {
    this->declare_parameter<std::string>("joint_name",    "joint1");
    this->declare_parameter<double>("gear_ratio",          1.0);
    this->declare_parameter<double>("bus_voltage",        14.8);
    this->declare_parameter<double>("current_limit",     80.0);
    this->declare_parameter<double>("load_inertia",      0.0);

    joint_name_    = this->get_parameter("joint_name").as_string();
    gear_ratio_    = this->get_parameter("gear_ratio").as_double();
    bus_voltage_   = this->get_parameter("bus_voltage").as_double();
    current_limit_ = this->get_parameter("current_limit").as_double();
    load_inertia_  = this->get_parameter("load_inertia").as_double();

    // ── Parameter validation ──────────────────────────────────────────────────
    if (gear_ratio_ <= 0.0) {
      RCLCPP_WARN(this->get_logger(),
        "gear_ratio must be > 0 (got %.3f), clamping to 1.0", gear_ratio_);
      gear_ratio_ = 1.0;
    }
    
    if (bus_voltage_ <= 0.0) {
      RCLCPP_WARN(this->get_logger(),
        "bus_voltage must be > 0 (got %.1f), clamping to 14.8V", bus_voltage_);
      bus_voltage_ = 14.8;
    }
    
    if (current_limit_ <= 0.0) {
      RCLCPP_WARN(this->get_logger(),
        "current_limit must be > 0 (got %.1f), clamping to 80.0A", current_limit_);
      current_limit_ = 80.0;
    }
    
    if (load_inertia_ < 0.0) {
      RCLCPP_WARN(this->get_logger(),
        "load_inertia cannot be negative (got %.3e), clamping to 0.0", load_inertia_);
      load_inertia_ = 0.0;
    }

    joint_state_publisher_ =
      this->create_publisher<sensor_msgs::msg::JointState>("/joint_states", 10);

    // Initialize base class publishers and subscription using parameterized topic names
    std::string status_topic = this->get_parameter("status_topic").as_string();
    std::string health_topic = this->get_parameter("health_topic").as_string();
    std::string control_topic = this->get_parameter("control_topic").as_string();
    
    status_publisher =
      this->create_publisher<motor_messages::msg::Feedback>(status_topic, 10);
    health_publisher =
      this->create_publisher<motor_messages::msg::Health>(health_topic, 10);
    control_subscription =
      this->create_subscription<motor_messages::msg::Command>(
        control_topic, 10,
        std::bind(&SimMotorController::control_callback, this, std::placeholders::_1));

    // Create timers for periodic publishing
    double status_freq = this->get_parameter("status_publish_frequency").as_double();
    double health_freq = this->get_parameter("health_publish_frequency").as_double();
    
    status_timer =
      this->create_wall_timer(
        std::chrono::milliseconds(static_cast<int>(1000.0 / status_freq)),
        std::bind(&SimMotorController::publish_status, this));
    
    health_timer =
      this->create_wall_timer(
        std::chrono::milliseconds(static_cast<int>(1000.0 / health_freq)),
        std::bind(&SimMotorController::publish_health, this));

    last_update_ = this->now();

    RCLCPP_INFO(this->get_logger(),
      "[SimMotorController] Kraken X44 model — joint='%s'  gear_ratio=%.2f  "
      "V_bus=%.1fV  I_limit=%.0fA  load_inertia=%.3e kg·m²",
      joint_name_.c_str(), gear_ratio_, bus_voltage_, current_limit_, load_inertia_);

    RCLCPP_INFO(this->get_logger(),
      "  R=%.5f Ω  L=%.1f µH  Ke=%.5f V·s/rad  Kt=%.5f N·m/A  "
      "J=%.3e kg·m²  b=%.3e N·m·s/rad",
      R_MOTOR, L_MOTOR * 1e6, KE, KT, J_ROTOR, B_VISC);
  }

private:
  // ── MotorControllerBase interface ──────────────────────────────────────────
  void control_callback(const motor_messages::msg::Command::SharedPtr msg) override;
  void publish_status() override;
  void publish_health() override;

  // ── ROS2 publishers ────────────────────────────────────────────────────────
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_state_publisher_;

  // ── Kraken X44 motor constants (all SI) ────────────────────────────────────
  // Source: WCP official datasheet — trapezoidal commutation mode
  //
  // Phase resistance  R  = V_supply / I_stall = 12 / 275
  static constexpr double R_MOTOR  = 0.04364;   // Ω
  //
  // Back-EMF constant Ke derived from free-speed operating point:
  //   Ke = (V - R·I_free) / ω_free = (12 - 0.04364·1.4) / 788.38
  static constexpr double KE       = 0.015142;  // V·s/rad
  //
  // Torque constant   Kt = 14.81 mN·m/A  (given directly by WCP)
  //   Cross-check: Kt·I_stall = 0.01481·275 = 4.07 N·m ≈ 4.05 N·m ✓
  static constexpr double KT       = 0.014810;  // N·m/A
  //
  // Phase inductance — not published; estimated for a 44 mm-class BLDC motor.
  // Gives electrical time constant τ_e = L/R ≈ 0.69 ms (< mechanical τ_m ≈ 3 ms).
  static constexpr double L_MOTOR  = 30.0e-6;   // H
  //
  // Rotor inertia — estimated from motor geometry (hollow rotor, r ≈ 15 mm, m ≈ 0.13 kg).
  //   J = m·r²/2 ≈ 1.46×10⁻⁵ kg·m²
  //   Gives mechanical time constant τ_m = J·R/(Kt·Ke) ≈ 2.8 ms
  static constexpr double J_ROTOR  = 1.46e-5;   // kg·m²
  //
  // Viscous friction b = Kt·I_free / ω_free = 0.01481·1.4 / 788.38
  static constexpr double B_VISC   = 2.630e-5;  // N·m·s/rad
  //
  // Free speed (rad/s) for reference: 7530 RPM = 788.38 rad/s
  static constexpr double OMEGA_FREE = 788.38;  // rad/s

  // ── Simulation state ───────────────────────────────────────────────────────
  double sim_current_   {0.0};   // stator current   [A]
  double sim_velocity_  {0.0};   // rotor velocity   [rad/s]
  double sim_position_  {0.0};   // rotor position   [rad]
  double sim_duty_cycle_{0.0};   // commanded duty cycle [-1, 1]

  // ── Config params ──────────────────────────────────────────────────────────
  std::string joint_name_;
  double gear_ratio_    {1.0};
  double bus_voltage_   {14.8};  // V
  double current_limit_ {80.0};  // A
  double load_inertia_  {0.0};   // kg·m²  (reflected load inertia)  

  // ── Position PID state ─────────────────────────────────────────────────────
  double pos_integral_  {0.0};
  double pos_prev_error_{0.0};
  // Gains — tune for your application; conservative defaults
  static constexpr double KP_POS = 6.0;
  static constexpr double KI_POS = 0.05;
  static constexpr double KD_POS = 0.25;

  // ── Integration ────────────────────────────────────────────────────────────
  rclcpp::Time last_update_;

  // Number of RK4 sub-steps per control callback.
  // τ_electrical ≈ 0.69 ms → 10 sub-steps at 10 ms loop = 1 ms/step (safe margin).
  static constexpr int RK4_SUBSTEPS = 50;

  struct State { double i, omega, theta; };

  /**
   * Compute state derivatives for the X44 electromechanical model.
   * @param s    current state {i, ω, θ}
   * @param V    applied voltage [V]
   */
  State derivatives(const State & s, double V) const;

  /** Advance state by dt using 4th-order Runge-Kutta. */
  State rk4_step(const State & s, double V, double dt) const;

  /** Integrate for total_dt using RK4_SUBSTEPS sub-steps. */
  void step_simulation(double total_dt);
};

} // namespace motor_control
