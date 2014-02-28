// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Collector.h"
#include "../Robotmap.h"
#include "../Commands/CollectorIdle.h"
#include "Math.h"
static Timer timeTravel;
Collector::Collector() : Subsystem("Collector") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	collectorLifter = RobotMap::collectorcollectorLifter;
	rollerMotor = RobotMap::collectorrollerMotor;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    timeTravel.Start();
}
    
void Collector::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new CollectorIdle());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
void Collector::MoveCollector(bool extend)
{
	if (extend == true)
	{
	    if (collectorLifter->Get() != DoubleSolenoid::kForward)
	    {
	        timeTravel.Reset();
	        timeTravel.Start();
	    }
		collectorLifter->Set(DoubleSolenoid::kForward);
	}
	else
	{
        if (collectorLifter->Get() != DoubleSolenoid::kReverse)
        {
            timeTravel.Reset();
            timeTravel.Start();
        }
		collectorLifter->Set(DoubleSolenoid::kReverse);
	}
}
void Collector::Pickup(float speed)
{
    rollerMotor->Set(-fabs(speed));
//    if (GetState() == DOWN)
//    else
//        rollerMotor->Set(0.0);
}
void Collector::Spit(float speed)
{
    
    rollerMotor->Set(fabs(speed));
//    if (GetState() == DOWN)
//    else
//        rollerMotor->Set(0.0);
}
void Collector::Idle()
{
	rollerMotor->Set(0.0);
}
Collector::CollectorState Collector::GetState()
{
	if ((timeTravel.Get() >= TIME_TRAVELING_UP) && (collectorLifter->Get() == DoubleSolenoid::kReverse))
	{
		return UP;
	}
	if ((timeTravel.Get() < TIME_TRAVELING_UP) && (collectorLifter->Get() == DoubleSolenoid::kReverse)) 
	{
		return TRAVELING_UP;
	}
	if ((timeTravel.Get() >= TIME_TRAVELING_DOWN) && (collectorLifter->Get() == DoubleSolenoid::kForward))
	{
		return DOWN;
	}
	if ((timeTravel.Get() < TIME_TRAVELING_DOWN) && (collectorLifter->Get() == DoubleSolenoid::kForward))
	{
		return TRAVELING_DOWN;
	}
	return IDLE;
}
