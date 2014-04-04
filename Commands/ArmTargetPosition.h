// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.


#ifndef ARMTARGETPOSITION_H
#define ARMTARGETPOSITION_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class ArmTargetPosition: public Command {
private:
    ShooterArm::ShooterArmPosition  _targetPosition;
public:
	ArmTargetPosition(ShooterArm::ShooterArmPosition target);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

class ArmTargetCollectorRestrictedPosition: public ArmTargetPosition {
public:
    ArmTargetCollectorRestrictedPosition(ShooterArm::ShooterArmPosition target):ArmTargetPosition(target){}
    virtual void Execute()
    {
        if (Robot::collector->GetState() == Collector::DOWN)
        {
            ArmTargetPosition::Execute();
        }
        else if (Robot::collector->GetState() != Collector::TRAVELING_DOWN)
        {
            Command *cmd = Robot::collector->GetCurrentCommand();
            if (cmd != (Command *)0)
                cmd->Cancel();
            
            Robot::collector->SetCollectorPosition(true);
        }
    }
    
};

class TargetAutonomous1: public ArmTargetCollectorRestrictedPosition {
public:
    TargetAutonomous1():ArmTargetCollectorRestrictedPosition(ShooterArm::AUTONOMOUS_1){}
};
class TargetAutonomous2: public ArmTargetCollectorRestrictedPosition {
public:
    TargetAutonomous2():ArmTargetCollectorRestrictedPosition(ShooterArm::AUTONOMOUS_2){}
};
class TargetAutonomous3: public ArmTargetCollectorRestrictedPosition {
public:
    TargetAutonomous3():ArmTargetCollectorRestrictedPosition(ShooterArm::AUTONOMOUS_3){}
};
class TargetAutonomousClose: public ArmTargetCollectorRestrictedPosition {
public:
    TargetAutonomousClose():ArmTargetCollectorRestrictedPosition(ShooterArm::AUTONOMOUS_CLOSE){}
};
class TargetTruss: public ArmTargetPosition {
public:
    TargetTruss():ArmTargetPosition(ShooterArm::TRUSS){}
};
class TargetEjectPosition: public ArmTargetCollectorRestrictedPosition {
public:
    TargetEjectPosition():ArmTargetCollectorRestrictedPosition(ShooterArm::EJECT){}
};
class TargetCatch: public ArmTargetPosition {
public:
    TargetCatch():ArmTargetPosition(ShooterArm::CATCH){}
};
class TargetLoadPosition: public ArmTargetCollectorRestrictedPosition {
public:
    TargetLoadPosition():ArmTargetCollectorRestrictedPosition(ShooterArm::LOAD){}
};
class TargetLongGoal: public ArmTargetCollectorRestrictedPosition {
public:
    TargetLongGoal():ArmTargetCollectorRestrictedPosition(ShooterArm::LONG_GOAL){}
};
class TargetLongTruss: public ArmTargetCollectorRestrictedPosition {
public:
    TargetLongTruss():ArmTargetCollectorRestrictedPosition(ShooterArm::LONG_TRUSS){}
};

class TargetReverseShortGoal: public ArmTargetPosition {
    TargetReverseShortGoal():ArmTargetPosition(ShooterArm::REVERSE_SHORT_GOAL){}
};

class TargetShortGoal: public ArmTargetPosition {
public:
    TargetShortGoal():ArmTargetPosition(ShooterArm::SHORT_GOAL){}
//    virtual void Execute()
//        {
//            if (Robot::collector->GetState() == Collector::UP)
//            {
//                ArmTargetPosition::Execute();
//            }
//            else if (Robot::collector->GetState() != Collector::TRAVELING_UP)
//            {
//                Command *cmd = Robot::collector->GetCurrentCommand();
//                if (cmd != (Command *)0)
//                    cmd->Cancel();
//                
//                Robot::collector->SetCollectorPosition(false);
//            }
//        }
};


#endif
