// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "ArmTargetShortGoal.h"
#include "../ShooterArmPositions.h"
ArmTargetShortGoal::ArmTargetShortGoal() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::shooterArm);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// Called just before this Command runs the first time
void ArmTargetShortGoal::Initialize() {
	
}
// Called repeatedly when this Command is scheduled to run
void ArmTargetShortGoal::Execute() {
	ShooterArm *arm = Robot::shooterArm;
					
	arm->SetTargetAngle(ARM_TARGET_SHORT_GOAL);
}
// Make this return true when this Command no longer needs to run execute()
bool ArmTargetShortGoal::IsFinished() {
	ShooterArm *arm = Robot::shooterArm;
					
	return arm->IsOnTarget();
}
// Called once after isFinished returns true
void ArmTargetShortGoal::End() {
	
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArmTargetShortGoal::Interrupted() {
}
