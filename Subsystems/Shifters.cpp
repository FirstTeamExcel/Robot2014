// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.



#include "Shifters.h"
#include "../Robotmap.h"
#include "../Commands/UpShift.h"

Shifters::Shifters() : Subsystem("Shifters") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	shiftSolenoid = RobotMap::shiftersshiftSolenoid;
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}
    
void Shifters::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new UpShift());
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void Shifters::ShiftDown()
{
	if(shiftSolenoid->Get() == DoubleSolenoid::kForward)
	{
		shiftSolenoid->Set(DoubleSolenoid::kReverse);
	}
}

void Shifters::ShiftUp()
{
	if(shiftSolenoid->Get() == DoubleSolenoid::kReverse)
	{
		shiftSolenoid->Set(DoubleSolenoid::kForward);
	}
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

