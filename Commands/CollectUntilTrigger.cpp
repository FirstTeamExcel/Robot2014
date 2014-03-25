// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.


#include "CollectUntilTrigger.h"

CollectUntilTrigger::CollectUntilTrigger():CollectThenFlip() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::collector);
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

// Make this return true when this Command no longer needs to run execute()
bool CollectUntilTrigger::IsFinished() {
	return (Robot::collector->flipperSwitch->Get());
}

// Called once after isFinished returns true
void CollectUntilTrigger::End() {
	Robot::collector->SetFlipperPosition(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CollectUntilTrigger::Interrupted() {
	Robot::collector->SetFlipperPosition(false);
}
