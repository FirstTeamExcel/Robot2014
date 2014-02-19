// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "CollectorDown.h"
#include "ShooterArmDismount.h"
#include "TargetAutonomous1.h"
#include "Shoot.h" 
#include "ShooterIdle.h"
#include "DriveTwoFeet.h"
#include "TargetAutonomous2.h"
#include "TargetLoadPosition.h"
#include "CollectorIdle.h"
#include "CollectorLoad.h"
#include "TargetAutonomous3.h"
#include "ThreeBallAutonomousCommand.h"
#include "ShooterSpinUp.h"
ThreeBallAutonomousCommand::ThreeBallAutonomousCommand() {
	AddSequential(new CollectorDown());
	AddParallel(new TargetAutonomous3());
	AddSequential(new ShooterSpinUp());
	AddSequential(new Shoot());
	AddSequential(new CollectorLoad());
	AddSequential(new TargetLoadPosition());
	AddParallel(new TargetAutonomous2());
	AddSequential(new ShooterSpinUp());
	AddSequential(new Shoot());
	AddSequential(new DriveTwoFeet());
	AddSequential(new CollectorLoad());
	AddSequential(new TargetLoadPosition());
	AddParallel(new TargetAutonomous1());
	AddParallel(new CollectorIdle());
	AddSequential(new ShooterSpinUp());
	AddSequential(new Shoot());
	AddSequential(new DriveTwoFeet());
	AddSequential(new DriveTwoFeet());
	
	
}
