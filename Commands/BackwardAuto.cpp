// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.



#include "BackwardAuto.h"
#include "ManualFlipperDown.h"
#include "CollectorDown.h"
#include "ShooterSetRpm.h"
#include "../ShooterWheelsSpeeds.h"
#include "Shoot.h" 
#include "DriveTwoSeconds.h"
#include "ArmTargetAngle.h"
#include "Collect.h"
#include "../ShooterArmPositions.h"
#include "CollectUntilTrigger.h"
#include "ArmTargetPosition.h"
#include "ManualFlipperUp.h"
#include "DriveToEncoderCommand.h"
#include "Delay.h"

BackwardAuto::BackwardAuto() {
	AddParallel(new ArmTargetAngle(ARM_TARGET_BACKWARDS_AUTONOMOUS));
	AddSequential(new CollectorDown());
	AddParallel(new ManualFlipperDown());
	AddSequential(new Collect(), 0.5);
	
	AddParallel(new CollectUntilTrigger(), 1.5);
	AddParallel(new ShooterSetRpm(1950));
	//AddSequential(new DriveTwoSeconds(2.25, -0.5));
	AddSequential(new DriveToEncoderCommand(4.4, -0.5),2.75);

    AddSequential(new Delay(), 0.5);
	AddSequential(new Shoot());
	AddParallel(new ShooterSetRpm(0.0));
	AddSequential(new TargetLoadPosition());
	
	AddParallel(new ShooterSetRpm(1950));
	AddSequential(new ArmTargetAngle(ARM_TARGET_BACKWARDS_AUTONOMOUS));

    AddSequential(new Delay(), 0.2);
	AddSequential(new Shoot());
	AddSequential(new ShooterSetRpm(0.0));
	
	
}
