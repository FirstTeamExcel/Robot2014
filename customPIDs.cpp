#include "customPIDs.h"
#include "DriverStationLCD.h"


GyroControlledTurning::GyroControlledTurning(RobotDrive *controlledRobot)
{
	theRobot = controlledRobot;
	offset = 0.20;
}

void GyroControlledTurning::PIDWrite(float output)
{

    DriverStationLCD *driverStationLCD = DriverStationLCD::GetInstance();
    driverStationLCD->PrintfLine((DriverStationLCD::Line) 1, "PIDout: %f", output);
	if (theRobot)
	{
	    if (output < 0.0)
	    {
	        theRobot->TankDrive((output - offset), (offset - output));
	    }
	    else if (output > 0.0)
	    {
	        theRobot->TankDrive((offset + output), -(offset + output));
	    }
	        
	}
}


SonarControlledDriving::SonarControlledDriving(RobotDrive *controlledRobot)
{
	theRobot = controlledRobot;
}

void SonarControlledDriving::PIDWrite(float output)
{
	if (theRobot)
		theRobot->TankDrive(-output, -output);
}
