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
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

bool ShooterPiston::Fire(float delay)
{
    static Timer shotTimer;
    bool returnValue = false;
    if ((Robot::shooterWheels->IsUpToSpeed() == true) && (ready == true) && (shotTimer.Get()
            > BALL_ESCAPE_TIME))
    {
        Robot::shooterWheels->StartTakeBack();
        firingSolenoid->Set(DoubleSolenoid::kForward);
        shotTimer.Start();
        shotTimer.Reset();
        ready = false;
        returnValue = true;
        return true;
    }
    // This function takes the takeBack back, Jack
    else if (shotTimer.Get() > delay)
    {
        shotTimer.Reset();
        ready = true;
        firingSolenoid->Set(DoubleSolenoid::kReverse);
    }
    else if (shotTimer.Get() == 0.0)
    {
        shotTimer.Start();
    }
    
    
    return returnValue;
}

bool ShooterPiston::IsShotComplete()
{
    bool shotComplete = false;
    if ((ready == true) && shotTimer.Get() >= 0.5)
    {
        shotComplete = true;
    }
    return shotComplete;
}
