// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "ShooterWheels.h"
#include "../Robotmap.h"
#include "../Commands/ShooterIdle.h"
ShooterWheels::ShooterWheels() : Subsystem("ShooterWheels") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	rightWheelMotor = RobotMap::shooterWheelsrightWheelMotor;
	leftWheelMotor = RobotMap::shooterWheelsleftWheelMotor;
	leftCounter = RobotMap::shooterWheelsleftCounter;
	rightCounter = RobotMap::shooterWheelsrightCounter;
	firingSolenoid = RobotMap::shooterWheelsFiringSolenoid;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
}
    
void ShooterWheels::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new ShooterIdle());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.

void ShooterWheels::SetTargetRpm(float targetRpm, float bias)
{
	if(targetRpm == 0)
	{
		targetSPR_Right = 0;
		targetSPR_Right = 0;
		targetSPR_Right_UpperLimit = 0;
		targetSPR_Left_UpperLimit = 0;
	}
	else
	{ 
		float rightTargetRpm;
		float leftTargetRpm;
		if (bias != 0.0)
		{
			rightTargetRpm = targetRpm * (1.0 + bias);
			leftTargetRpm = targetRpm * (1.0 - bias);
		}
		else
		{
			rightTargetRpm = targetRpm;
			leftTargetRpm = targetRpm;
		}
		if(rightTargetRpm > MAX_RPM)
		{
			rightTargetRpm = MAX_RPM;
		}
		if(leftTargetRpm > MAX_RPM)
		{
			leftTargetRpm = MAX_RPM;
		}
		targetSPR_Right = ((double)60.0) / ((double)rightTargetRpm);
		targetSPR_Left = ((double)60.0) / ((double)leftTargetRpm);
		targetSPR_Right_UpperLimit = (targetSPR_Right * (1.0 + SPEED_TOLERANCE));
		targetSPR_Left_UpperLimit = (targetSPR_Left * (1.0 + SPEED_TOLERANCE));
		targetSPR_Right_LowerLimit = (targetSPR_Right * (1.0 - SPEED_TOLERANCE));
		targetSPR_Left_LowerLimit = (targetSPR_Left * (1.0 - SPEED_TOLERANCE));
	}
}

void ShooterWheels::SetPower(float power)
{
	rightWheelMotor->Set(power);
	leftWheelMotor->Set(power);
}
float ShooterWheels::GetRpm()
{
	rightCount.Get();
	return leftCount.Get();
}
bool ShooterWheels::Fire(float delay)
{
	firingSolenoid->Set(DoubleSolenoid::kForward);
	return true;
}

void ShooterWheels::Run()
{
	
}
