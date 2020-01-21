/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/SubsystemBase.h>
#include "tigertronics/SwerveDrivetrain.h"
#include "tigertronics/RosBridge/RosBridgeWsClient.h"
#include "tigertronics/RosBridge/RosTypes.h"
#include <units/units.h>

static std::shared_ptr<RosTypes::Twist> twist = std::make_shared<RosTypes::Twist>();

class SwerveSubsystem : public frc2::SubsystemBase {
 public:
  SwerveSubsystem();
  void DriveWithJoystick(double x, double y, double rot, bool fieldRelative);
  void DriveWithRos(units::meters_per_second_t xSpeed, units::meters_per_second_t ySpeed, units::radians_per_second_t rotSpeed);
  const frc::Pose2d& GetCurrentPose();
  const frc::Twist2d& GetCurrentTwist();
  std::vector<double> GetIMUData();
  void Periodic() override;
  void SendOdometry();
  void SendIMU();
  void ManualWheelMove(std::string wheel, int abs_setpoint);
  void ManualWheelMove(std::string wheel, units::radian_t angle, units::meters_per_second_t speed);
  std::shared_ptr<RosTypes::Twist> GetTwist();
  RosTypes::Odometry ConstructOdom(const frc::Pose2d& currentPose, const frc::Twist2d& currentTwist);
  RosTypes::IMU ConstructIMU(double roll, double pitch, double yaw, double velX, double velY, double velZ, double accelX, double accelY, double accelZ);
  void ChangeRosConnection(std::string uri);
 private:
  int seqOdom = 0;
  int seqImu = 0;
  RosBridgeWsClient rbc{};
  frc::Pose2d currentPose;
  frc::Twist2d currentTwist;
  std::vector<double> currentIMUData;
  std::string jetson_ip = "192.168.1.115";
  SwerveDrivetrain m_swerve;
};
