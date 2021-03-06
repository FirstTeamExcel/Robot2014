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
#include "ArmTargetPosition.h"
#include "Shoot.h" 
#include "DriveTwoFeet.h"
#include "CollectorIdle.h"
#include "CollectorLoad.h"
#include "ThreeBallAutonomousCommand.h"
#include "ShooterSetRpm.h"
#include "../ShooterWheelsSpeeds.h"
ThreeBallAutonomousCommand::ThreeBallAutonomousCommand() {
	AddSequential(new CollectorDown());
	//Collector acquire, turn on rollers slowly
	AddSequential(new TargetAutonomous3());
    //AddSequential(new ShooterSetRpm(TARGET_AUTONOMOUS_3_SPEED));
	//AddSequential(new Shoot());
	//AddSequential(new CollectorLoad(), 2.0);//Shorter if acquire works
	//Drive forward slowly for remainder of auton
	//Collector acquire
	AddSequential(new TargetLoadPosition());
	AddSequential(new TargetAutonomous2());
    //AddSequential(new ShooterSetRpm(TARGET_AUTONOMOUS_2_SPEED));
	//AddSequential(new Shoot());
	//AddParallel(new CollectorLoad(), 2.0);//Shorter if we acquired the ball
	//AddSequential(new DriveTwoFeet());//Unneccessary if we were driving
	AddSequential(new TargetLoadPosition());
    AddSequential(new TargetAutonomous1());
    AddSequential(new ShooterSetRpm(TARGET_AUTONOMOUS_3_SPEED));
	//AddSequential(new CollectorIdle());
    //AddSequential(new ShooterSetRpm(TARGET_AUTONOMOUS_1_SPEED));
	//AddSequential(new Shoot());
    //AddSequential(new ShooterSetRpm(0.0));
//	AddSequential(new DriveTwoFeet());
//	AddSequential(new DriveTwoFeet());
	
	
}
