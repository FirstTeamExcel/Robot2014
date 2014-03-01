// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "OI.h"
//#define VERBOSE_DASHBOARD
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/ArcadeDrive.h"
#include "Commands/ArmTargetPosition.h"
#include "Commands/AutoTarget.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/CameraTuning.h"
#include "Commands/CatchClose.h"
#include "Commands/CatchOpen.h"
#include "Commands/CheesyDrive.h"
#include "Commands/Collect.h"
#include "Commands/CollectorDown.h"
#include "Commands/CollectorEject.h"
#include "Commands/CollectorIdle.h"
#include "Commands/CollectorLoad.h"
#include "Commands/CollectorUP.h"
#include "Commands/CompressorStart.h"
#include "Commands/CompressorStop.h"
#include "Commands/CradleEject.h"
#include "Commands/DetectHotGoal.h"
#include "Commands/DownShift.h"
#include "Commands/Drive.h"
#include "Commands/DriveStraightTuning.h"
#include "Commands/DriveTwoFeet.h"
#include "Commands/EjectBallCommand.h"
#include "Commands/ForceShot.h"
#include "Commands/LoadBallCommand.h"
#include "Commands/PoweredShot.h"
#include "Commands/Shoot.h"
#include "Commands/ShooterArmTuningMode.h"
#include "Commands/ShooterIdle.h"
#include "Commands/ShooterPistonIdle.h"
#include "Commands/ShooterSetRpm.h"
#include "Commands/ShooterSpinUp.h"
#include "Commands/ShooterWheelsAutoTarget.h"
#include "Commands/ShotTuning.h"
#include "Commands/SingleBallAutonomousCommand.h"
#include "Commands/SpinLongGoal.h"
#include "Commands/SpinShortGoal.h"
#include "Commands/SpinTruss.h"
#include "Commands/StartingPosition.h"
#include "Commands/TargetStartPosition.h"
#include "Commands/ThreeBallAutonomousCommand.h"
#include "Commands/Turn180Degrees.h"
#include "Commands/Turn90Degrees.h"
#include "Commands/TurnToAngleTurning.h"
#include "Commands/TurtleStance.h"
#include "Commands/TwoBallAutonomousCommand.h"
#include "Commands/UpShift.h"
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/ArmTargetPosition.h"
OI::OI() {
	// Process operator interface input here.
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	operatorStick = new Joystick(3);
	
	catcherClose = new JoystickButton(operatorStick, 4);
	catcherClose->WhenPressed(new CatchClose());
	catcherOpen = new JoystickButton(operatorStick, 6);
	catcherOpen->WhenPressed(new CatchOpen());
	targetLoadPosition = new JoystickButton(operatorStick, 11);
	targetLoadPosition->WhileHeld(new LoadBallCommand());
	targetTruss = new JoystickButton(operatorStick, 9);
	targetTruss->WhileHeld(new SpinTruss());
	targetShortShot = new JoystickButton(operatorStick, 10);
	targetShortShot->WhileHeld(new SpinShortGoal());
	targetLongShot = new JoystickButton(operatorStick, 7);
	targetLongShot->WhileHeld(new SpinLongGoal());
	alsoEject = new JoystickButton(operatorStick, 12);
	alsoEject->WhileHeld(new EjectBallCommand());
	alsoCollectorUp = new JoystickButton(operatorStick, 5);
	alsoCollectorUp->WhenPressed(new CollectorUP());
	alsoCollectorDown = new JoystickButton(operatorStick, 3);
	alsoCollectorDown->WhileHeld(new LoadBallCommand());
	forceShotButton = new JoystickButton(operatorStick, 2);
	forceShotButton->WhileHeld(new ForceShot());
	alsoShootBall = new JoystickButton(operatorStick, 1);
	alsoShootBall->WhileHeld(new Shoot());
	rightDriveStick = new Joystick(2);
	
	collectorUp = new JoystickButton(rightDriveStick, 3);
	collectorUp->WhileHeld(new CollectorUP());
	collectorDown = new JoystickButton(rightDriveStick, 2);
	collectorDown->WhileHeld(new Collect());
	shiftDown = new JoystickButton(rightDriveStick, 1);
	shiftDown->WhileHeld(new TurtleStance());
	leftDriveStick = new Joystick(1);
	
	eject = new JoystickButton(leftDriveStick, 5);
	eject->WhileHeld(new EjectBallCommand());
	spinUp = new JoystickButton(leftDriveStick, 2);
	spinUp->WhileHeld(new ShooterSpinUp());
	shootBall = new JoystickButton(leftDriveStick, 1);
	shootBall->WhileHeld(new ForceShot());
     
        // SmartDashboard Buttons
	SmartDashboard::PutData("Collect", new Collect());
	SmartDashboard::PutData("AutoTarget", new AutoTarget());
	SmartDashboard::PutData("ShooterArmTuningMode", new ShooterArmTuningMode());
	SmartDashboard::PutData("DriveStraightTuning", new DriveStraightTuning());
	SmartDashboard::PutData("TurnToAngleTurning", new TurnToAngleTurning());
	SmartDashboard::PutData("DetectHotGoal", new DetectHotGoal());
	SmartDashboard::PutData("CameraTuning", new CameraTuning());
	SmartDashboard::PutData("ShotTuning", new ShotTuning());
	SmartDashboard::PutData("StartingPosition", new StartingPosition());
	SmartDashboard::PutData("SpinTruss", new SpinTruss());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	
#ifdef VERBOSE_DASHBOARD
    SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());
    SmartDashboard::PutData("SingleBallAutonomousCommand", new SingleBallAutonomousCommand());
    SmartDashboard::PutData("TwoBallAutonomousCommand", new TwoBallAutonomousCommand());
    SmartDashboard::PutData("ThreeBallAutonomousCommand", new ThreeBallAutonomousCommand());
    SmartDashboard::PutData("CollectorIdle", new CollectorIdle());
    SmartDashboard::PutData("CollectorUP", new CollectorUP());
    SmartDashboard::PutData("CollectorLoad", new CollectorLoad());
    SmartDashboard::PutData("CollectorDown", new CollectorDown());
    SmartDashboard::PutData("CollectorEject", new CollectorEject());
    SmartDashboard::PutData("Collect", new Collect());
    SmartDashboard::PutData("ShooterIdle", new ShooterIdle());
    SmartDashboard::PutData("PoweredShot", new PoweredShot());
    SmartDashboard::PutData("ShooterSpinUp", new ShooterSpinUp());
    SmartDashboard::PutData("ShooterWheelsAutoTarget", new ShooterWheelsAutoTarget());
    SmartDashboard::PutData("ShooterPistonIdle", new ShooterPistonIdle());
    SmartDashboard::PutData("Shoot", new Shoot());
    SmartDashboard::PutData("BlockerRaise", new BlockerRaise());
    SmartDashboard::PutData("BlockerLower", new BlockerLower());
    SmartDashboard::PutData("BlockerIdle", new BlockerIdle());
    SmartDashboard::PutData("TargetTruss", new TargetTruss());
    SmartDashboard::PutData("TargetLongGoal", new TargetLongGoal());
    SmartDashboard::PutData("TargetShortGoal", new TargetShortGoal());
    SmartDashboard::PutData("ShooterArmDismount", new ShooterArmDismount());
    SmartDashboard::PutData("ArmSecureCatch", new ArmSecureCatch());
    SmartDashboard::PutData("TargetLoadPosition", new TargetLoadPosition());
    SmartDashboard::PutData("TargetEjectPosition", new TargetEjectPosition());
    SmartDashboard::PutData("ArmCatchPosition", new ArmCatchPosition());
    SmartDashboard::PutData("DriveTwoFeet", new DriveTwoFeet());
    SmartDashboard::PutData("Drive", new Drive());
    SmartDashboard::PutData("Turn90Degrees", new Turn90Degrees());
    SmartDashboard::PutData("Turn180Degrees", new Turn180Degrees());
    SmartDashboard::PutData("DownShift", new DownShift());
    SmartDashboard::PutData("UpShift", new UpShift());
    SmartDashboard::PutData("CheesyDrive", new CheesyDrive());
    SmartDashboard::PutData("ArcadeDrive", new ArcadeDrive());
    SmartDashboard::PutData("CompressorStart", new CompressorStart());
    SmartDashboard::PutData("CompressorStop", new CompressorStop());
    SmartDashboard::PutData("LoadBall", new LoadBall());
    SmartDashboard::PutData("TargetStartPosition", new TargetStartPosition());
    SmartDashboard::PutData("CatchClose", new CatchClose());
    SmartDashboard::PutData("CatchOpen", new CatchOpen());
#endif
    spinChooser = new SendableChooser();
    spinChooser->AddDefault("Speed Control", new ShooterSpinUp());
    spinChooser->AddObject("Full Power",  new PoweredShot());
    SmartDashboard::PutData("Wheel Mode:", spinChooser);
}
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
Joystick* OI::getoperatorStick() {
	return operatorStick;
}
Joystick* OI::getrightDriveStick() {
	return rightDriveStick;
}
Joystick* OI::getleftDriveStick() {
	return leftDriveStick;
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
void OI::UpdateShotType()
{
    static Command *prevSelection;
    Command *selection = (Command *) spinChooser->GetSelected();
    if (prevSelection != selection)
    {
        spinUp->WhileHeld(selection);
        prevSelection = selection;
    }    
}
