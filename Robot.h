// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#ifndef _ROBOT_H
#define _ROBOT_H
#include "WPILib.h"
#include "Commands/Command.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/AutonomousCommand.h"
#include "Subsystems/Camera.h"
#include "Subsystems/Collector.h"
#include "Subsystems/CompressorSubsystem.h"
#include "Subsystems/DriveSubsystem.h"
#include "Subsystems/Shifters.h"
#include "Subsystems/ShooterArm.h"
#include "Subsystems/ShooterPiston.h"
#include "Subsystems/ShooterWheels.h"
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "OI.h"
class Robot : public IterativeRobot {
private:
    Command *defaultAuton;
public:
	Command *autonomousCommand;
	SendableChooser *autoChooser;
	static OI *oi;
	LiveWindow *lw;
	
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static DriveSubsystem* driveSubsystem;
	static ShooterArm* shooterArm;
	static ShooterWheels* shooterWheels;
	static Collector* collector;
	static Camera* camera;
	static Shifters* shifters;
	static ShooterPiston* shooterPiston;
	static CompressorSubsystem* compressorSubsystem;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
//	static Robot* theRobot;
	//static Preferences *preferences;
	
	virtual void RobotInit();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();
    virtual void DisabledInit();
    virtual void DisabledPeriodic();
};
#endif
