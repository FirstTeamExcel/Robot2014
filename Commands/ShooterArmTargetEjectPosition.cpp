// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "ShooterArmTargetEjectPosition.h"
#include "../ShooterArmPositions.h"
#include "../Subsystems/ShooterArm.h"
#include "../Subsystems/Collector.h"
ShooterArmTargetEjectPosition::ShooterArmTargetEjectPosition() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::shooterArm);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// Called just before this Command runs the first time
void ShooterArmTargetEjectPosition::Initialize() {
	
}
// Called repeatedly when this Command is scheduled to run
void ShooterArmTargetEjectPosition::Execute() {
	if (Robot::collector->DOWN)
	{
		ShooterArm *arm = Robot::shooterArm;
					
		arm->SetTargetPosition(ShooterArm::EJECT);
	}
}
// Make this return true when this Command no longer needs to run execute()
bool ShooterArmTargetEjectPosition::IsFinished() {
	ShooterArm *arm = Robot::shooterArm;
				
	return arm->IsOnTarget();
}
// Called once after isFinished returns true
void ShooterArmTargetEjectPosition::End() {
	
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterArmTargetEjectPosition::Interrupted() {
}
