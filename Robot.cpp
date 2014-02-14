// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Robot.h"
#include "Commands/SingleBallAutonomousCommand.h"
#include "Commands/TwoBallAutonomousCommand.h"
#include "Commands/ThreeBallAutonomousCommand.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
DriveSubsystem* Robot::driveSubsystem = 0;
ShooterArm* Robot::shooterArm = 0;
ShooterWheels* Robot::shooterWheels = 0;
Collector* Robot::collector = 0;
Blocker* Robot::blocker = 0;
Camera* Robot::camera = 0;
Shifters* Robot::shifters = 0;
ShooterPiston* Robot::shooterPiston = 0;
CompressorSubsystem* Robot::compressorSubsystem = 0;
OI* Robot::oi = 0;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
void Robot::RobotInit()
{
    RobotMap::init();
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	driveSubsystem = new DriveSubsystem();
	shooterArm = new ShooterArm();
	shooterWheels = new ShooterWheels();
	collector = new Collector();
	blocker = new Blocker();
	camera = new Camera();
	shifters = new Shifters();
	shooterPiston = new ShooterPiston();
	compressorSubsystem = new CompressorSubsystem();
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    // This MUST be here. If the OI creates Commands (which it very likely
    // will), constructing it during the construction of CommandBase (from
    // which commands extend), subsystems are not guaranteed to be
    // yet. Thus, their requires() statements may grab null pointers. Bad
    // news. Don't move it.
    oi = new OI();
    lw = LiveWindow::GetInstance();
    // instantiate the command used for the autonomous period
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	autonomousCommand = new AutonomousCommand();
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
    autoChooser = new SendableChooser();
    autoChooser->AddDefault("Single Ball Auton", new SingleBallAutonomousCommand());
    autoChooser->AddObject("Two Ball Auton", new TwoBallAutonomousCommand());
    autoChooser->AddObject("Three Ball Auton", new ThreeBallAutonomousCommand());
    SmartDashboard::PutData("Autonomous Mode:", autoChooser);
}
void Robot::AutonomousInit()
{
    autonomousCommand = (Command *) autoChooser->GetSelected();
    if (autonomousCommand != NULL)
        autonomousCommand->Start();
}
void Robot::AutonomousPeriodic()
{
    Scheduler::GetInstance()->Run();
}
void Robot::TeleopInit()
{
    // This makes sure that the autonomous stops running when
    // teleop starts running. If you want the autonomous to 
    // continue until interrupted by another command, remove
    // this line or comment it out.
    autonomousCommand->Cancel();
}
void Robot::TeleopPeriodic()
{
    Scheduler::GetInstance()->Run();
    float leftRPM, rightRPM;
    shooterWheels->GetRpm(rightRPM,leftRPM);
    SmartDashboard::PutNumber("Right RPM",leftRPM);
    SmartDashboard::PutNumber("Right RPM",rightRPM);
    SmartDashboard::PutNumber("Arm Angle", shooterArm->GetCurrentAngle());
}
void Robot::TestPeriodic()
{
    lw->Run();
    float leftRPM, rightRPM;
    shooterWheels->GetRpm(rightRPM,leftRPM);
    SmartDashboard::PutNumber("Right RPM",leftRPM);
    SmartDashboard::PutNumber("Right RPM",rightRPM);
    SmartDashboard::PutNumber("Arm Angle", shooterArm->GetCurrentAngle());
}

void Robot::DisabledInit()
{

}

void Robot::DisabledPeriodic()
{
    SmartDashboard::PutNumber("Arm Angle", shooterArm->GetCurrentAngle());
    
}

START_ROBOT_CLASS(Robot)
;
