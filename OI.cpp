// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "OI.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/ArmTargetAutonomous1.h"
#include "Commands/ArmTargetAutonomous2.h"
#include "Commands/ArmTargetAutonomous3.h"
#include "Commands/ArmTargetLongGoal.h"
#include "Commands/ArmTargetShortGoal.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/BlockerIdle.h"
#include "Commands/BlockerLower.h"
#include "Commands/BlockerRaise.h"
#include "Commands/CollectorDown.h"
#include "Commands/CollectorEject.h"
#include "Commands/CollectorIdle.h"
#include "Commands/CollectorLoad.h"
#include "Commands/CollectorUP.h"
#include "Commands/Drive.h"
#include "Commands/DriveStraightTuning.h"
#include "Commands/DriveTwoFeet.h"
#include "Commands/EjectBall.h"
#include "Commands/Shoot.h"
#include "Commands/ShootTargetTruss.h"
#include "Commands/ShooterArmAutoTarget.h"
#include "Commands/ShooterArmDismount.h"
#include "Commands/ShooterArmTargetEjectPosition.h"
#include "Commands/ShooterArmTargetLoadPosition.h"
#include "Commands/ShooterArmTargetTruss.h"
#include "Commands/ShooterArmTuningMode.h"
#include "Commands/ShooterIdle.h"
#include "Commands/ShooterSpinUp.h"
#include "Commands/ShooterTargetGoal.h"
#include "Commands/ShooterWheelTargetLoadPosition.h"
#include "Commands/ShooterWheelsAutoTarget.h"
#include "Commands/ShooterWheelsManualControl.h"
#include "Commands/ShooterWheelsTargetEjectPosition.h"
#include "Commands/ShooterWheelsTargetTruss.h"
#include "Commands/ShooterWheelsTuningMode.h"
#include "Commands/SingleBallAutonomousCommand.h"
#include "Commands/ThreeBallAutonomousCommand.h"
#include "Commands/Turn180Degrees.h"
#include "Commands/Turn90Degrees.h"
#include "Commands/TurnToAngleTurning.h"
#include "Commands/TwoBallAutonomousCommand.h"
#include "Commands/WheelTargetAutonomous1.h"
#include "Commands/WheelTargetAutonomous2.h"
#include "Commands/WheelTargetAutonomous3.h"
#include "Commands/WheelTargetLongGoal.h"
#include "Commands/WheelTargetShortGoal.h"
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
OI::OI() {
	// Process operator interface input here.
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	operatorStick = new Joystick(3);
	
	rightDriveStick = new Joystick(2);
	
	leftDriveStick = new Joystick(1);
	
     
        // SmartDashboard Buttons
	SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());
	SmartDashboard::PutData("Shoot", new Shoot());
	SmartDashboard::PutData("CollectorUP", new CollectorUP());
	SmartDashboard::PutData("CollectorLoad", new CollectorLoad());
	SmartDashboard::PutData("CollectorDown", new CollectorDown());
	SmartDashboard::PutData("CollectorEject", new CollectorEject());
	SmartDashboard::PutData("ShootTargetTruss", new ShootTargetTruss());
	SmartDashboard::PutData("ShooterSpinUp", new ShooterSpinUp());
	SmartDashboard::PutData("ShooterTargetGoal", new ShooterTargetGoal());
	SmartDashboard::PutData("SingleBallAutonomousCommand", new SingleBallAutonomousCommand());
	SmartDashboard::PutData("Drive", new Drive());
	SmartDashboard::PutData("ShooterIdle", new ShooterIdle());
	SmartDashboard::PutData("CollectorIdle", new CollectorIdle());
	SmartDashboard::PutData("BlockerRaise", new BlockerRaise());
	SmartDashboard::PutData("BlockerLower", new BlockerLower());
	SmartDashboard::PutData("BlockerIdle", new BlockerIdle());
	SmartDashboard::PutData("TwoBallAutonomousCommand", new TwoBallAutonomousCommand());
	SmartDashboard::PutData("ThreeBallAutonomousCommand", new ThreeBallAutonomousCommand());
	SmartDashboard::PutData("ShooterWheelsTargetTruss", new ShooterWheelsTargetTruss());
	SmartDashboard::PutData("ShooterArmTargetTruss", new ShooterArmTargetTruss());
	SmartDashboard::PutData("ArmTargetLongGoal", new ArmTargetLongGoal());
	SmartDashboard::PutData("ArmTargetShortGoal", new ArmTargetShortGoal());
	SmartDashboard::PutData("ArmTargetAutonomous1", new ArmTargetAutonomous1());
	SmartDashboard::PutData("ArmTargetAutonomous2", new ArmTargetAutonomous2());
	SmartDashboard::PutData("WheelTargetLongGoal", new WheelTargetLongGoal());
	SmartDashboard::PutData("ArmTargetAutonomous3", new ArmTargetAutonomous3());
	SmartDashboard::PutData("WheelTargetShortGoal", new WheelTargetShortGoal());
	SmartDashboard::PutData("WheelTargetAutonomous1", new WheelTargetAutonomous1());
	SmartDashboard::PutData("WheelTargetAutonomous3", new WheelTargetAutonomous3());
	SmartDashboard::PutData("WheelTargetAutonomous2", new WheelTargetAutonomous2());
	SmartDashboard::PutData("ShooterArmAutoTarget", new ShooterArmAutoTarget());
	SmartDashboard::PutData("ShooterWheelsAutoTarget", new ShooterWheelsAutoTarget());
	SmartDashboard::PutData("ShooterArmTargetLoadPosition", new ShooterArmTargetLoadPosition());
	SmartDashboard::PutData("ShooterWheelTargetLoadPosition", new ShooterWheelTargetLoadPosition());
	SmartDashboard::PutData("ShooterArmTargetEjectPosition", new ShooterArmTargetEjectPosition());
	SmartDashboard::PutData("ShooterWheelsTargetEjectPosition", new ShooterWheelsTargetEjectPosition());
	SmartDashboard::PutData("ShooterWheelsManualControl", new ShooterWheelsManualControl());
	SmartDashboard::PutData("ShooterArmTuningMode", new ShooterArmTuningMode());
	SmartDashboard::PutData("ShooterWheelsTuningMode", new ShooterWheelsTuningMode());
	SmartDashboard::PutData("EjectBall", new EjectBall());
	SmartDashboard::PutData("DriveTwoFeet", new DriveTwoFeet());
	SmartDashboard::PutData("Turn90Degrees", new Turn90Degrees());
	SmartDashboard::PutData("Turn180Degrees", new Turn180Degrees());
	SmartDashboard::PutData("DriveStraightTuning", new DriveStraightTuning());
	SmartDashboard::PutData("TurnToAngleTurning", new TurnToAngleTurning());
	SmartDashboard::PutData("ShooterArmDismount", new ShooterArmDismount());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
Joystick* OI::getoperatorStick() {
	return operatorStick;
}
Joystick* OI::getrightDriveStick() {
	return rightDriveStick;
}
Joystick* OI::getleftDriveStick() {
	return leftDriveStick;
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
