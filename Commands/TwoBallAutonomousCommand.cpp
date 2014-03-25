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
#include "Shoot.h" 
#include "DriveTwoFeet.h"
#include "DriveTwoSeconds.h"
#include "ArmTargetPosition.h"
#include "CollectUntilTrigger.h"
#include "CollectorUP.h"
#include "CollectorDown.h"
#include "TwoBallAutonomousCommand.h"
#include "ShooterSetRpm.h"
#include "LoadBallCommand.h"
#include "../ShooterWheelsSpeeds.h"
TwoBallAutonomousCommand::TwoBallAutonomousCommand()
{
    AddSequential(new CollectorDown());
    AddParallel(new TargetAutonomous2());//1.2s
    AddSequential(new ShooterSetRpm(TARGET_AUTONOMOUS_2_SPEED));//1.5s
    AddSequential(new Shoot());//2.2s
    AddParallel(new TargetTruss());
    AddParallel(new ShooterSetRpm(0.0));
    AddSequential(new CollectUntilTrigger(), 2.0);//4.2s
    AddSequential(new TargetLoadPosition());//4.7s
    AddParallel(new ShooterSetRpm(TARGET_AUTONOMOUS_2_SPEED));//6.2s
    AddSequential(new TargetAutonomous2());
    AddSequential(new Shoot());//6.9s
    AddSequential(new ShooterSetRpm(0.0));
    AddSequential(new DriveTwoSeconds());
}
