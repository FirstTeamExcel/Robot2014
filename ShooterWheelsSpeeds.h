#ifndef SHOOTERWHEELS_SPEEDS_H
#define SHOOTERWHEELS_SPEEDS_H


#define TARGET_LONG_GOAL_SPEED (3300)
#define TARGET_AUTONOMOUS_1_SPEED (3300)
#define TARGET_AUTONOMOUS_2_SPEED (3300)
#define TARGET_AUTONOMOUS_3_SPEED (3300)

#define TARGET_SHORT_GOAL_SPEED (3200)
#define TARGET_TRUSS_SPEED (3200)

#define TARGET_EJECT_POWER (0.4)
#define TARGET_LOAD_POWER (-0.4)



#define SPEED_TOLERANCE (0.15)
#define MAX_RPM (5000)
#define MAX_BIAS (0.2)
#define TAKE_BACK_TIME (0.4)
#define TAKE_BACK_POWER (0.8)
#define AUTONOMOUS_BIAS (0.1)

//Firing  Parameters
#define BALL_ESCAPE_TIME (TAKE_BACK_TIME)  //How long the piston remains extended when fired
#define PISTON_RETRACT_TIME (0.2)  //How long the piston remains extended when fired

#endif //SHOOTERWHEELS_SPEEDS_H
