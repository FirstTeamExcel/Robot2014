// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "DriveSubsystem.h"
#include "../Robotmap.h"
#include "../Commands/Drive.h"
DriveSubsystem::DriveSubsystem() :
    Subsystem("DriveSubsystem"), driveOutput(), turnOutput(),
            turnToAngleOutput(RobotMap::driveSubsystemTheDriveTrain)
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	leftDrive = RobotMap::driveSubsystemleftDrive;
	rightDrive = RobotMap::driveSubsystemrightDrive;
	theDriveTrain = RobotMap::driveSubsystemTheDriveTrain;
	leftEncoder = RobotMap::driveSubsystemleftEncoder;
	rightEncoder = RobotMap::driveSubsystemrightEncoder;
	driveGyro = RobotMap::driveSubsystemdriveGyro;
	driveAccelerometer = RobotMap::driveSubsystemdriveAccelerometer;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    leftEncoder->SetPIDSourceParameter(PIDSource::kDistance);
    rightEncoder->SetPIDSourceParameter(PIDSource::kDistance);
    leftEncoder->SetDistancePerPulse(INCHES_PER_PULSE);
    rightEncoder->SetDistancePerPulse(INCHES_PER_PULSE);
    driveStraightPID = new PIDController(DRIVE_STRAIGHT_P, DRIVE_STRAIGHT_I,
            DRIVE_STRAIGHT_D, driveGyro, &turnOutput);
    driveDistancePID = new PIDController(DRIVE_DISTANCE_P, DRIVE_DISTANCE_I,
            DRIVE_DISTANCE_D, leftEncoder, &driveOutput);
    turnToAnglePID = new PIDController(TURN_ANGLE_P, TURN_ANGLE_I,
            TURN_ANGLE_D, driveGyro, &turnToAngleOutput);
}
void DriveSubsystem::InitDefaultCommand()
{
    // Set the default command for a subsystem here.
    //SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
	SetDefaultCommand(new Drive());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
bool DriveSubsystem::DriveStraight(float inchesToDrive)
{
    bool retValue = false;
    static Timer onTargetTimer;
    
    driveDistancePID->SetSetpoint(inchesToDrive);
    if (inchesToDrive > 0.0)
    {
        
        driveDistancePID->SetOutputRange(-0.3, 0.8);
    }
    else
    {
        
        driveDistancePID->SetOutputRange(-0.8, 0.3);
    }
    driveStraightPID->SetSetpoint(0.0);
    
    if (driveDistancePID->IsEnabled() == false)
    {
        driveDistancePID->Enable();
        driveStraightPID->Enable();
    }
    
    if (driveDistancePID->OnTarget())
    {
        if (onTargetTimer.Get() == 0.4)
        {
            driveDistancePID->Disable();
            driveStraightPID->Disable();
            retValue = true;
        }
    }
    else
    {
        onTargetTimer.Reset();
        onTargetTimer.Start();
        theDriveTrain->Drive(driveOutput.GetOutput(), turnOutput.GetOutput());
    }
    return retValue;
}
bool DriveSubsystem::TurnToAngle(float totalTurnAngle)
{
    bool retValue = false;
    static Timer onTargetTimer;
    if (turnToAnglePID->IsEnabled() == false)
    {
        float turnedAngle = driveGyro->GetAngle() + totalTurnAngle;
        turnToAnglePID->SetSetpoint(turnedAngle);
        turnToAnglePID->Enable();
    }
    if (turnToAnglePID->OnTarget())
    {
        if (onTargetTimer.Get() == 0.4)
        {
            turnToAnglePID->Disable();
            retValue = true;
        }
    }
    else
    {
        onTargetTimer.Reset();
        onTargetTimer.Start();
    }
    return retValue;
}
