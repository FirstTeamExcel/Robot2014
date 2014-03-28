// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#ifndef OI_H
#define OI_H
#include "WPILib.h"
class OI {
private:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	Joystick* driveController;
	JoystickButton* shiftDownButton;
	JoystickButton* shiftUpButton;
	JoystickButton* collectorIntake;
	JoystickButton* collectorSpit;
	JoystickButton* invertDrive;
	JoystickButton* overrideShot;
	JoystickButton* upSpin;
	JoystickButton* ballShoot;
	JoystickButton* downCollector;
	JoystickButton* upCollector;
	Joystick* operatorStick;
	JoystickButton* catcherClose;
	JoystickButton* catcherOpen;
	JoystickButton* targetLoadPosition;
	JoystickButton* targetTruss;
	JoystickButton* targetShortShot;
	JoystickButton* targetLongShot;
	JoystickButton* tossBall;
	JoystickButton* rollerControl;
	JoystickButton* flipperUp;
	JoystickButton* forceShotButton;
	JoystickButton* alsoShootBall;
	Joystick* throttleDriveStick;
	JoystickButton* collectorUp;
	JoystickButton* collectorDown;
	JoystickButton* shiftDown;
	Joystick* steeringDriveStick;
	JoystickButton* invertDrive2;
	JoystickButton* driverForceShot;
	JoystickButton* shootBall;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	SendableChooser *spinChooser;
	SendableChooser *controlChooser;
public:
	OI();
 
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
	Joystick* getsteeringDriveStick();
	Joystick* getthrottleDriveStick();
	Joystick* getoperatorStick();
	Joystick* getdriveController();
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
	bool GetLongShotType();
	bool IsDriverUsingController();
};
#endif
