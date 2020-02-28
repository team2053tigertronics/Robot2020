#pragma once

#include <frc2/command/CommandHelper.h>
#include <frc2/command/InstantCommand.h>
#include "subsystems/ClimberSubsystem.h"

class ClimbBrakeOn
    : public frc2::CommandHelper<frc2::InstantCommand,
                                 ClimbBrakeOn> {
 public:
  ClimbBrakeOn(ClimberSubsystem* climbSub);

  void Initialize() override;
 private: 
  ClimberSubsystem* m_climberSubsystem;
};
