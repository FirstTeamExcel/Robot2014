#ifndef SHOOTERWHEELS_SPEEDS_H
#define SHOOTERWHEELS_SPEEDS_H

#define	WHEELS_SPINNING_UP

#define WHEELS_SPINNING_DOWN

#define UPPER_RPM_LIMIT(rpm) (rpm + (rpm*0.1))

#define LOWER_RPM_LIMIT(rpm) (rpm - (rpm*0.1))

#define MAX_RPM (5000)

#define TARGET_LONG_GOAL_SPEED (.9)

#define TARGET_SHORT_GOAL_SPEED (.5)

#define TARGET_LOAD_SPEED (-0.3)

#define TARGET_EJECT_SPEED (0.4)

#define TARGET_TRUSS_SPEED (0.9)

#define TARGET_AUTO_SPEED (0.8)

#define MAX_BIAS (0.2)



#endif //SHOOTERWHEELS_SPEEDS_H
