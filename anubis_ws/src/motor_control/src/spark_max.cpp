/**
 * @file SparkMax.cpp
 * @brief Source file for the SparkMax class for controlling REV Robotics SPARK MAX controllers
 * @author Grayson Arendt
 */

 #include "motor_control/SparkMax.hpp"

 SparkMax::SparkMax(const std::string & interfaceName, uint8_t deviceId)
 : SparkBase(interfaceName, deviceId) {}