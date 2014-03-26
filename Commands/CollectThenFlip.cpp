// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "CollectThenFlip.h"
#include "../Subsystems/Collector.h"
CollectThenFlip::CollectThenFlip(float power): Collect(power) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::collector);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// Called just before this Command runs the first time
void CollectThenFlip::Initialize() {
    _wasTriggered = false;
    Collect::Initialize();
}
// Called repeatedly when this Command is scheduled to run
void CollectThenFlip::Execute() {
    _wasTriggered |= Robot::collector->SwitchHit();
    Collect::Execute();
}
// Make this return true when this Command no longer needs to run execute()
bool CollectThenFlip::IsFinished() {
	return false;
}
// Called once after isFinished returns true
void CollectThenFlip::End() {
    _wasTriggered |= Robot::collector->SwitchHit();
    if (_wasTriggered)
    {
        Robot::collector->SetFlipperPosition(false);
    }
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CollectThenFlip::Interrupted() {
	End();
}
