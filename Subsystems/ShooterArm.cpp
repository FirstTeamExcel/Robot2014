// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "ShooterArm.h"
#include "../Robotmap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PID
ShooterArm::ShooterArm() : PIDSubsystem("ShooterArm", 1.0, 0.0, 0.0) {
	SetAbsoluteTolerance(0.2);
	GetPIDController()->SetContinuous(false);
	LiveWindow::GetInstance()->AddActuator("ShooterArm", "PIDSubsystem Controller", GetPIDController());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PID
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	shooterArmPot = RobotMap::shooterArmshooterArmPot;
	shooterArmMotor = RobotMap::shooterArmshooterArmMotor;
	grabber = RobotMap::shooterArmGrabber;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	// Use these to get going:
	// SetSetpoint() -  Sets where the PID controller should move the system
	//                  to
	// Enable() - Enables the PID controller.
}
double ShooterArm::ReturnPIDInput() {
	// Return your input value for the PID loop
	// e.g. a sensor, like a potentiometer:
	// yourPot->SetAverageVoltage() / kYourMaxVoltage;	
	return VOLTAGE_TO_ANGLE(shooterArmPot->GetAverageVoltage());
}
void ShooterArm::UsePIDOutput(double output) {
	// Use output to drive your system, like a motor
	// e.g. yourMotor->Set(output);
	output = PIDOutputToMotorCommand(output);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=OUTPUT
	shooterArmMotor->PIDWrite(output);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=OUTPUT
}
void ShooterArm::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//setDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}

void ShooterArm::SetTargetAngle(float tgtAngle) {
	if (IsOnTarget() != true)
	{
		GetPIDController()->SetSetpoint(tgtAngle);
	}
}
bool ShooterArm::IsOnTarget() {
	return OnTarget();
}
float ShooterArm::GetCurrentAngle() {
	return(VOLTAGE_TO_ANGLE(shooterArmPot->GetAverageVoltage()));
}
float PIDOutputToMotorCommand(double output) {
	//TODO: add trig equation to figure the level of torque needed to move the arm up or down from a given position
	//TODO: logic to determine if the arm will move clockwise or counter-clockwise
}
