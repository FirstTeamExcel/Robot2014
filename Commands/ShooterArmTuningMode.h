// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.


#ifndef SHOOTERARMTUNINGMODE_H
#define SHOOTERARMTUNINGMODE_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class ShooterArmTuningMode: public Command {
private:
    float _p;
    float _i1;
    float _i2;
    float _tol1;
    float _tol2;
    float _d1;
    float _d2;
    float _f;
    float _angle;
    bool _enabled;
public:
	ShooterArmTuningMode();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
