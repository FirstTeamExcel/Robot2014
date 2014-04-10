// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "ManualFlipperUp.h"
#include "Math.h"
ManualFlipperUp::ManualFlipperUp() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// Called just before this Command runs the first time
void ManualFlipperUp::Initialize() {
	Robot::collector->SetFlipperPosition(false);
	if ((Robot::collector->GetState() == Collector::DOWN) &&
	        (Robot::collector->GetFlipperState() == Collector::F_DOWN) && 
	        (Robot::collector->rollerMotor->Get() == 0.0))
	{
	    Robot::collector->Pickup(0.51);
	}
	
}
// Called repeatedly when this Command is scheduled to run
void ManualFlipperUp::Execute() {
    float spd = fabs(Robot::collector->rollerMotor->Get());
    if (spd == 0.51)
    {
        Robot::collector->Pickup(0.52);
        
    }
    else if (spd == 0.52)
    {
        Robot::collector->Idle();
    }
}
// Make this return true when this Command no longer needs to run execute()
bool ManualFlipperUp::IsFinished() {
    return (Robot::collector->GetFlipperState() == Collector::F_UP);
}
// Called once after isFinished returns true
void ManualFlipperUp::End() {
	
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ManualFlipperUp::Interrupted() {
}
