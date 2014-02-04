// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#ifndef DRIVESUBSYSTEM_H
#define DRIVESUBSYSTEM_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../DummyPIDOutput.h"
#include "../CustomPIDs.h"

#define WHEEL_CIRCUMFERENCE 12.566370614359172953850573533118 //4" diameter wheel * pi 
#define ENCODER_TO_WHEEL_RATIO 4//TODO what is this supposed to be?
#define ENCODER_COUNTS_PER_REVOLUTION 400//TODO what is this supposed to be?

#define DRIVE_DISTANCE_P 0.1
#define DRIVE_DISTANCE_I 0.1
#define DRIVE_DISTANCE_D 0.1

#define DRIVE_STRAIGHT_P 0.1
#define DRIVE_STRAIGHT_I 0.1
#define DRIVE_STRAIGHT_D 0.1

#define TURN_ANGLE_P 0.1
#define TURN_ANGLE_I 0.1
#define TURN_ANGLE_D 0.1
/**
 *
 *
 * @author ExampleAuthor
 */
class DriveSubsystem: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
        static const float upShiftAcceleration = 1.1;

        
        static const double INCHES_PER_PULSE = WHEEL_CIRCUMFERENCE / (ENCODER_TO_WHEEL_RATIO * ENCODER_COUNTS_PER_REVOLUTION);
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	SpeedController* leftRearDrive;
	SpeedController* leftFrontDrive;
	SpeedController* rightFrontDrive;
	SpeedController* rightRearDrive;
	RobotDrive* theDriveTrain;
	Encoder* leftEncoder;
	Encoder* rightEncoder;
	Gyro* driveGyro;
	Accelerometer* driveAccelerometer;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	DummyPIDOutput driveOutput;
	DummyPIDOutput turnOutput;
	GyroControlledTurning turnToAngleOutput;
	
	PIDController* driveStraightPID;
	PIDController* driveDistancePID;
	PIDController* turnToAnglePID;
	
	DriveSubsystem();
	
	void InitDefaultCommand();
	
	bool DriveStraight(float inchesToDrive);
	bool TurnToAngle(float totalTurnAngle);
};
#endif
