// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.


#ifndef DRIVESTRAIGHTTUNING_H
#define DRIVESTRAIGHTTUNING_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class DriveStraightTuning: public Command {
private:
    float _drive_p;
    float _drive_i;
    float _drive_d;
    float _straight_p;
    float _straight_i;
    float _straight_d;
    float _distance;
    bool _enabled;
public:
	DriveStraightTuning();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
