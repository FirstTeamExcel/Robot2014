// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "ShooterPiston.h"
#include "../Robotmap.h"
#include "../Robot.h"
#include "../ShooterWheelsSpeeds.h"
#include "../Commands/ShooterPistonIdle.h"
ShooterPiston::ShooterPiston() : Subsystem("ShooterPiston") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	firingSolenoid = RobotMap::shooterPistonFiringSolenoid;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	ready = true;    
	shotTimer.Start();
}
    
void ShooterPiston::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new ShooterPistonIdle());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
bool ShooterPiston::Fire(float delay)
{
    bool returnValue = false;
    if ((Robot::shooterWheels->IsUpToSpeed() == true) && (ready == true) && (shotTimer.HasPeriodPassed(delay) ))
    {
        Robot::shooterWheels->StartTakeBack();
        firingSolenoid->Set(DoubleSolenoid::kReverse);
        shotTimer.Reset();
        ready = false;
        returnValue = true;
        return true;
    }
    
    return returnValue;
}
bool ShooterPiston::IsShotComplete()
{
    bool shotComplete = false;
    if ((ready == true) && shotTimer.HasPeriodPassed(BALL_ESCAPE_TIME))
    {
        shotComplete = true;
    }
    return shotComplete;
}
void ShooterPiston::Idle()
{
    if (shotTimer.HasPeriodPassed(BALL_ESCAPE_TIME))
    {
        shotTimer.Reset();
        ready = true;
        firingSolenoid->Set(DoubleSolenoid::kForward);
    }
}
