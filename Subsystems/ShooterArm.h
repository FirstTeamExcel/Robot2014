// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#ifndef SHOOTERARM_H
#define SHOOTERARM_H
#include "Commands/PIDSubsystem.h"
#include "WPILib.h"
/**
 *
 *
 * @author ExampleAuthor
 */
class ShooterArm: public PIDSubsystem {
 public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	AnalogChannel* shooterArmPot;
	SpeedController* shooterArmMotor;
	DoubleSolenoid* grabber;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	ShooterArm();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();
	static const double TARGET = 1.0;
	static const double TRUSS = 3.0;
	static const double PASS = 0.0;
};
#endif