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
	Joystick* operatorStick;
	JoystickButton* catcherClose;
	JoystickButton* catcherOpen;
	JoystickButton* targetLoadPosition;
	JoystickButton* targetTruss;
	JoystickButton* targetShortShot;
	JoystickButton* targetLongShot;
	JoystickButton* tossBall;
	JoystickButton* cradleEjectButton;
	JoystickButton* alsoCollectorDown;
	JoystickButton* forceShotButton;
	JoystickButton* alsoShootBall;
	Joystick* rightDriveStick;
	JoystickButton* collectorUp;
	JoystickButton* collectorDown;
	JoystickButton* shiftDown;
	Joystick* leftDriveStick;
	JoystickButton* eject;
	JoystickButton* spinUp;
	JoystickButton* shootBall;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	SendableChooser *spinChooser;
public:
	OI();
 
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
	Joystick* getleftDriveStick();
	Joystick* getrightDriveStick();
	Joystick* getoperatorStick();
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES
	void UpdateShotType();
};
#endif
