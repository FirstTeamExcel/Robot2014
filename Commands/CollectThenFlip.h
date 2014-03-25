// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.


#ifndef COLLECTTHENFLIP_H
#define COLLECTTHENFLIP_H


#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "Collect.h"
/**
 *
 *
 * @author ExampleAuthor
 */
class CollectThenFlip: public Collect {
private:
	bool _wasTriggered;
public:
	CollectThenFlip(float power = 0.0);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
