// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "DriveStraightTuning.h"
#include "../Subsystems/DriveSubsystem.h"
DriveStraightTuning::DriveStraightTuning() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::driveSubsystem);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
    DriveSubsystem *driveSub = Robot::driveSubsystem;
    PIDController *drive = driveSub->driveDistancePID;
    PIDController *straight = driveSub->driveStraightPID;
    _drive_p = drive->GetP();
    _drive_i = drive->GetI();
    _drive_d = drive->GetD();
    
    _straight_p = straight->GetP();
    _straight_i = straight->GetI();
    _straight_d = straight->GetD();
    _distance = 0.0;    
}
// Called just before this Command runs the first time
void DriveStraightTuning::Initialize() {
    _enabled = false;
    _distance = 0.0;
    Robot::driveSubsystem->driveGyro->Reset();
    Robot::driveSubsystem->leftEncoder->Reset();
    Robot::driveSubsystem->rightEncoder->Reset();
        
    SmartDashboard::PutNumber("Distance",_distance);
    SmartDashboard::PutBoolean("Enable", _enabled);
    SmartDashboard::PutNumber("Drive P",_drive_p);
    SmartDashboard::PutNumber("Drive i",_drive_i);
    SmartDashboard::PutNumber("Drive d",_drive_d);
    SmartDashboard::PutNumber("Straight P",_straight_p);
    SmartDashboard::PutNumber("Straight i",_straight_i);
    SmartDashboard::PutNumber("Straight d",_straight_d);
}
// Called repeatedly when this Command is scheduled to run
void DriveStraightTuning::Execute() {
    DriveSubsystem *driveSub = Robot::driveSubsystem;
    _drive_p = SmartDashboard::GetNumber("Drive P");
    _drive_i = SmartDashboard::GetNumber("Drive i");
    _drive_d = SmartDashboard::GetNumber("Drive d");
    _straight_p = SmartDashboard::GetNumber("Straight P");
    _straight_i = SmartDashboard::GetNumber("Straight i");
    _straight_d = SmartDashboard::GetNumber("Straight d");
    _distance = SmartDashboard::GetNumber("Distance");
     _enabled = SmartDashboard::GetBoolean("Enable");
     static bool prevEnabled = false; 
     if ((_enabled == true) && (prevEnabled == false))
     {
         PIDController *drive = driveSub->driveDistancePID;
         PIDController *straight = driveSub->driveStraightPID;
         drive->SetPID(_drive_p,_drive_i,_drive_d);
         straight->SetPID(_straight_p,_straight_i,_straight_d);
         driveSub->DriveStraight(_distance);
     }
     else if (_enabled == false)
     {
         driveSub->Cancel();
         prevEnabled = false;
     }
}
// Make this return true when this Command no longer needs to run execute()
bool DriveStraightTuning::IsFinished() {
	return false;
}
// Called once after isFinished returns true
void DriveStraightTuning::End() {
	
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveStraightTuning::Interrupted() {
    Robot::driveSubsystem->Cancel();
}
