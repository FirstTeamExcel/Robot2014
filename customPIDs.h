#ifndef CUSTOMPIDS_H
#define CUSTOMPIDS_H

#include "PIDOutput.h"
#include "RobotDrive.h"

#define ENABLE_PID_ROTATION
//#define ENABLE_PID_RANGE_FINDER
class GyroControlledTurning: public PIDOutput
{
private:
	RobotDrive *theRobot;
	float offset;
public:
	GyroControlledTurning(RobotDrive *controlledRobot);
	void PIDWrite(float output);
	void SetOffset(float inOffset){offset = inOffset;}
};

class SonarControlledDriving: public PIDOutput
{
private:
	RobotDrive *theRobot;
public:
	SonarControlledDriving(RobotDrive *controlledRobot);
	void PIDWrite(float output);
};

#endif
