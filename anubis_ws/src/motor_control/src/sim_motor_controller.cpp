#include "motor_control/sim_motor_controller.hpp"
#include <rclcpp/rclcpp.hpp>

namespace motor_control
{

  // ── Electromechanical model ───────────────────────────────────────────────────
  SimMotorController::State
  SimMotorController::derivatives(const State &s, double V) const
  {
    // Enforce current limit (clamp the effective voltage driving current above limit)
    double effective_V = V;
    if ((s.i > current_limit_ && V > 0.0) ||
        (s.i < -current_limit_ && V < 0.0))
    {
      effective_V = 0.0; // Let back-EMF + resistance naturally reduce current
    }

    // Electrical:  L·di/dt = V_app - R·i - Ke·ω
    double J_effective = J_ROTOR + load_inertia_ / (gear_ratio_ * gear_ratio_);

    // Safeguard against zero/invalid inertia
    if (J_effective <= 0.0 || std::isnan(J_effective) || std::isinf(J_effective))
    {
      J_effective = J_ROTOR; // Fall back to rotor inertia only
    }

    double di_dt = (effective_V - R_MOTOR * s.i - KE * s.omega) / L_MOTOR;

    // Mechanical:  J·dω/dt = Kt·i - b·ω
    double domega_dt = (KT * s.i - B_VISC * s.omega) / J_effective;

    // Kinematic:   dθ/dt = ω
    double dtheta_dt = s.omega;

    // Final sanity check: if any output is NaN, return zeros (motor is stalled)
    if (std::isnan(di_dt) || std::isnan(domega_dt) || std::isnan(dtheta_dt))
    {
      return {0.0, 0.0, s.omega}; // Stop accelerating, keep velocity as-is
    }

    return {di_dt, domega_dt, dtheta_dt};
  }

  SimMotorController::State
  SimMotorController::rk4_step(const State &s, double V, double dt) const
  {
    auto k1 = derivatives(s, V);

    State s2 = {
        s.i + 0.5 * dt * k1.i,
        s.omega + 0.5 * dt * k1.omega,
        s.theta + 0.5 * dt * k1.theta};
    auto k2 = derivatives(s2, V);

    State s3 = {
        s.i + 0.5 * dt * k2.i,
        s.omega + 0.5 * dt * k2.omega,
        s.theta + 0.5 * dt * k2.theta};
    auto k3 = derivatives(s3, V);

    State s4 = {
        s.i + dt * k3.i,
        s.omega + dt * k3.omega,
        s.theta + dt * k3.theta};
    auto k4 = derivatives(s4, V);

    return {
        s.i + (dt / 6.0) * (k1.i + 2 * k2.i + 2 * k3.i + k4.i),
        s.omega + (dt / 6.0) * (k1.omega + 2 * k2.omega + 2 * k3.omega + k4.omega),
        s.theta + (dt / 6.0) * (k1.theta + 2 * k2.theta + 2 * k3.theta + k4.theta)};
  }

  void SimMotorController::step_simulation(double total_dt)
  {
    if (total_dt <= 0.0)
    {
      return;
    }

    double V_applied = std::clamp(sim_duty_cycle_, -1.0, 1.0) * bus_voltage_;
    double sub_dt = total_dt / RK4_SUBSTEPS;

    State s = {sim_current_, sim_velocity_, sim_position_};

    for (int k = 0; k < RK4_SUBSTEPS; ++k)
    {
      s = rk4_step(s, V_applied, sub_dt);
    }

    // Validate state after integration
    if (std::isnan(s.i) || std::isinf(s.i))
    {
      RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 1000,
                           "Current became NaN/Inf, resetting to 0");
      s.i = 0.0;
    }
    if (std::isnan(s.omega) || std::isinf(s.omega))
    {
      RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 1000,
                           "Velocity became NaN/Inf, resetting to 0");
      s.omega = 0.0;
    }
    if (std::isnan(s.theta) || std::isinf(s.theta))
    {
      RCLCPP_WARN_THROTTLE(this->get_logger(), *this->get_clock(), 1000,
                           "Position became NaN/Inf, resetting to 0");
      s.theta = 0.0;
    }

    // Clamp to reasonable physical limits
    s.i = std::clamp(s.i, -1000.0, 1000.0);         // Current should never exceed ±1000A
    s.omega = std::clamp(s.omega, -2000.0, 2000.0); // ~19,000 RPM max (very generous)

    sim_current_ = s.i;
    sim_velocity_ = s.omega;
    sim_position_ = s.theta;
  }

  // ── control_callback ──────────────────────────────────────────────────────────

  void SimMotorController::control_callback(
      const motor_messages::msg::Command::SharedPtr msg)
  {
    auto now = this->now();

    if (last_update_.nanoseconds() == 0)
    {
      last_update_ = now;
      return;
    }


    double dt = (now - last_update_).seconds();


    last_update_ = now;

    if (dt <= 0.0 || dt > 1.0) {
    RCLCPP_WARN(this->get_logger(), "Large dt detected (%.2f s). Skipping physics step.", dt);
    return;
  }

    if (std::abs(msg->dutycycle.data) > 1e-6)
    {
      // ── Duty-cycle / open-loop mode ──────────────────────────────────────
      sim_duty_cycle_ = msg->dutycycle.data;
      pos_integral_ = 0.0; // reset integrator on mode switch
      pos_prev_error_ = 0.0;
    }
    else if (std::abs(msg->position.data) > 1e-6)
    {
      // ── Position closed-loop mode (PID → duty cycle) ─────────────────────
      // Joint-space position command converted to motor-shaft position
      double cmd_motor_pos = static_cast<double>(msg->position.data) * gear_ratio_;
      double error = cmd_motor_pos - sim_position_;

      pos_integral_ += error * dt;
      double derivative = (dt > 0.0) ? (error - pos_prev_error_) / dt : 0.0;
      pos_prev_error_ = error;

      double output = KP_POS * error + KI_POS * pos_integral_ + KD_POS * derivative;
      sim_duty_cycle_ = std::clamp(output, -1.0, 1.0);

      RCLCPP_DEBUG(this->get_logger(),
                   "pos_cmd=%.3f  cur=%.3f  err=%.3f  duty=%.3f",
                   cmd_motor_pos, sim_position_, error, sim_duty_cycle_);
    }
    else
    {
      // ── Stop ─────────────────────────────────────────────────────────────
      sim_duty_cycle_ = 0.0;
      pos_integral_ = 0.0;
      pos_prev_error_ = 0.0;
    }

    step_simulation(dt);
  }

  // ── publish_status ────────────────────────────────────────────────────────────

  void SimMotorController::publish_status()
  {
    // Feedback message (existing message type)
    motor_messages::msg::Feedback feedback;
    feedback.current.data = static_cast<float>(sim_current_);
    // Joint-space position/velocity = motor-shaft values divided by gear ratio
    feedback.position.data = static_cast<float>(sim_position_ / gear_ratio_);
    feedback.velocity.data = static_cast<float>(sim_velocity_ / gear_ratio_);
    feedback.is_disabled.data = false;
    status_publisher->publish(feedback);

    // JointState for Gazebo / RViz
    sensor_msgs::msg::JointState js;
    js.header.stamp = this->now();
    js.name.push_back(joint_name_);
    js.position.push_back(sim_position_ / gear_ratio_);
    js.velocity.push_back(sim_velocity_ / gear_ratio_);
    // effort expressed as estimated torque at the joint output
    js.effort.push_back(KT * sim_current_ * gear_ratio_);
    joint_state_publisher_->publish(js);
  }

  // ── publish_health ────────────────────────────────────────────────────────────

  void SimMotorController::publish_health()
  {
    // Simple thermal model: temperature rises proportionally to I²·R losses,
    // capped at a 60 °C operating ceiling (realistic for a sealed motor).
    static double temperature = 25.0;
    double power_loss = sim_current_ * sim_current_ * R_MOTOR;
    // τ_thermal ≈ 30 s (rough FRC motor estimate)
    constexpr double TAU_THERMAL = 30.0;
    constexpr double T_AMBIENT = 25.0;
    constexpr double THERMAL_RES = 1.2; // °C/W  (estimated for motor body)
    double T_steady = T_AMBIENT + THERMAL_RES * power_loss;
    temperature += (T_steady - temperature) * (1.0 / TAU_THERMAL); // ~1 Hz call rate

    motor_messages::msg::Health health;
    health.current.data = static_cast<float>(sim_current_);
    health.temperature.data = static_cast<float>(temperature);
    health.voltage.data = static_cast<float>(bus_voltage_);
    health.is_failed.data = (std::abs(sim_current_) > 300.0 || temperature > 90.0);
    health_publisher->publish(health);
  }

} // namespace motor_control
