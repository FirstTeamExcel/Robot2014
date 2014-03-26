// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "CheesyDrive.h"
CheesyDrive::CheesyDrive() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::driveSubsystem);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// Called just before this Command runs the first time
void CheesyDrive::Initialize() {
    Robot::driveSubsystem->Cancel();
	
}
// Called repeatedly when this Command is scheduled to run
void CheesyDrive::Execute() {
    //Cheesy Drive
    float ohSoCheesy=Robot::oi->getrightDriveStick()->GetY();
    float wowThatsCheesy=Robot::oi->getleftDriveStick()->GetX();
    Robot::driveSubsystem->theDriveTrain->ArcadeDrive(-ohSoCheesy, wowThatsCheesy);
    
//    float twist = logitechF310temp.GetTwist();//this should be the right stick forward/back
//    float x = logitechF310temp.GetX();
//    float y = logitechF310temp.GetY();
//    float z = logitechF310temp.GetZ();
//    printf("x: %f\ty: %f\tz: %f\n",x,y,z);
    
    
//    Robot::driveSubsystem->theDriveTrain->ArcadeDrive(-logitechF310temp.GetY(),logitechF310temp.GetZ());
}
// Make this return true when this Command no longer needs to run execute()
bool CheesyDrive::IsFinished() {
	return false;
}
// Called once after isFinished returns true
void CheesyDrive::End() {
	
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CheesyDrive::Interrupted() {
}
float CheesyDrive::GetThrottle()
{
    if (Robot::oi->IsDriverUsingController())
    {
        return -(Robot::oi->getdriveController()->GetY());
    }
    else
    {
        return -(Robot::oi->getrightDriveStick()->GetY());
    }
}
float CheesyDrive::GetSteering()
{
    if (Robot::oi->IsDriverUsingController())
    {
        return Robot::oi->getdriveController()->GetZ();
    }
    else
    {
        return Robot::oi->getleftDriveStick()->GetX();
    }
}
