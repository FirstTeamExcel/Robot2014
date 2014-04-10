// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.


#include "WaitForHotGoal.h"
#include "../CheesyVisionServer.h"

WaitForHotGoal::WaitForHotGoal() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}

// Called just before this Command runs the first time
void WaitForHotGoal::Initialize() {
	
}

// Called repeatedly when this Command is scheduled to run
void WaitForHotGoal::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool WaitForHotGoal::IsFinished() {
	//return (Robot::camera->GetHotGoal() == Camera::goalLeft) || (Robot::camera->GetHotGoal() == Camera::goalRight);
    return (CheesyVisionServer::GetInstance()->GetLeftStatus() && CheesyVisionServer::GetInstance()->GetRightStatus());
}

// Called once after isFinished returns true
void WaitForHotGoal::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void WaitForHotGoal::Interrupted() {

}
