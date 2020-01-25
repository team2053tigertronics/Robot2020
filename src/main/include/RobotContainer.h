/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/Command.h>

#include <frc/XboxController.h>
#include "commands/drive/TeleopDrive.h"
#include "subsystems/SwerveSubsystem.h"
#include "subsystems/ControlPanelSubsystem.h"
#include "commands/controlpanel/ManualWheelRotation.h"
#include "commands/controlpanel/RotationControl.h"
#include "commands/controlpanel/PositionControl.h"

/**
 * This class is where the bulk of the robot should be declared.  Since
 * Command-based is a "declarative" paradigm, very little robot logic should
 * actually be handled in the {@link Robot} periodic methods (other than the
 * scheduler calls).  Instead, the structure of the robot (including subsystems,
 * commands, and button mappings) should be declared here.
 */
class RobotContainer {
 public:
  RobotContainer();

  SwerveSubsystem m_drivetrain;
  ControlPanelSubsystem m_controlpanel;

 private:

  frc::XboxController driverController{0};
  frc::XboxController operatorController{1};

  // The robot's subsystems and commands are defined here...


  void ConfigureButtonBindings();
};
