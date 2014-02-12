// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "ShooterSpinUp.h"
#include "../Subsystems/ShooterWheels.h"
#include "../Subsystems/ShooterArm.h"
ShooterSpinUp::ShooterSpinUp() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::shooterWheels);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// Called just before this Command runs the first time
void ShooterSpinUp::Initialize() {
	
}
// Called repeatedly when this Command is scheduled to run
void ShooterSpinUp::Execute() {
	ShooterArm::ShooterArmPosition position = ShooterArm::GetTargetPosition();
	switch(position)
	{
	case ShooterArm::LOAD:
		Robot::shooterWheels->SetTargetRpm(TARGET_LOAD_SPEED);
		break;
	case ShooterArm::EJECT:
		Robot::shooterWheels->SetTargetRpm(TARGET_EJECT_SPEED);
		break;
	case ShooterArm::LONG_GOAL:
		Robot::shooterWheels->SetTargetRpm(TARGET_LONG_GOAL_SPEED);
		break;
	case ShooterArm::SHORT_GOAL:
		Robot::shooterWheels->SetTargetRpm(TARGET_SHORT_GOAL_SPEED);
		break;
	case ShooterArm::TRUSS:
		Robot::shooterWheels->SetTargetRpm(TARGET_TRUSS_SPEED);
		break;
	case ShooterArm::AUTONOMOUS_1:
		Robot::shooterWheels->SetTargetRpm(TARGET_AUTO_SPEED);
		break;
	case ShooterArm::AUTONOMOUS_2:
		Robot::shooterWheels->SetTargetRpm(TARGET_AUTO_SPEED);
		break;
	case ShooterArm::AUTONOMOUS_3:
		Robot::shooterWheels->SetTargetRpm(TARGET_AUTO_SPEED);
		break;
	default:
		SetTargetAngle(SHOOTER_ARM_TARGET_LOAD_POSITION);
		break;
	}
}
// Make this return true when this Command no longer needs to run execute()
bool ShooterSpinUp::IsFinished() {
	return false;
}
// Called once after isFinished returns true
void ShooterSpinUp::End() {
	
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterSpinUp::Interrupted() {
}
