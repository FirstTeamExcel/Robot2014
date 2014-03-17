#error //This file isn't ready for use

//Shooter Arm Position Preferences
#define SHOOTER_ARM_TARGET_EJECT_POSITION 35.0
#define SHOOTER_ARM_TARGET_LOAD_POSITION 0.0
#define SHOOTER_ARM_TARGET_TRUSS 70.0
#define SHOOTER_ARM_TARGET_CATCH 100.0
#define ARM_TARGET_LONG_GOAL 41.0
#define ARM_TARGET_AUTONOMOUS_1 43.5
#define ARM_TARGET_AUTONOMOUS_2 43.5
#define ARM_TARGET_AUTONOMOUS_3 ARM_TARGET_LONG_GOAL
#define ARM_TARGET_SHORT_GOAL 50.0
#define SHOOTER_ARM_DISMOUNT 85.0
#define ARM_START_POSITION 63.0

//Shooter Arm PID Preferences

//Shooter Wheel Preferences

#define SPEED_TOLERANCE (0.3)
#define MAX_RPM (3600)

#define TARGET_LONG_GOAL_SPEED (3500)
#define TARGET_AUTONOMOUS_1_SPEED (TARGET_LONG_GOAL_SPEED)
#define TARGET_AUTONOMOUS_2_SPEED (TARGET_LONG_GOAL_SPEED)
#define TARGET_AUTONOMOUS_3_SPEED (TARGET_LONG_GOAL_SPEED)
#define TARGET_SHORT_GOAL_SPEED (TARGET_LONG_GOAL_SPEED)
#define TARGET_TRUSS_SPEED (2200)
#define TARGET_EJECT_POWER (0.5)
#define TARGET_LOAD_POWER (-0.2)
#define TAKE_BACK_POWER (1.0)

//Shooter Piston Preferences
#define TAKE_BACK_TIME (0.4)
#define BALL_ESCAPE_TIME (TAKE_BACK_TIME)  //How long the piston remains extended when fired
#define PISTON_RETRACT_TIME (0.2)  //How long the piston remains extended when fired

//Camera Preferences
#define THRESHOLD_HSV 70, 155, 200, 255, 32, 210
#define AREA_MINIMUM 60
#define HEIGHT_MINIMUM 20

//Collector Preferences
#define TIME_TRAVELING_UP 0.5
#define TIME_TRAVELING_DOWN 0.3
#define TARGET_LOAD_SPEED (-0.5)
#define TARGET_EJECT_SPEED (0.5)

//Misc Preferences


