// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "ShooterArm.h"
#include "../Robotmap.h"
#include "SmartDashboard/SmartDashboard.h"
#include "LiveWindow/LiveWindow.h"
#include "Math.h"
#include "../ShooterArmPositions.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PID
ShooterArm::ShooterArm() : PIDSubsystem("ShooterArm", 0.75, 0.16, 0.7) {
	SetAbsoluteTolerance(0.3);
	GetPIDController()->SetContinuous(false);
	LiveWindow::GetInstance()->AddActuator("ShooterArm", "PIDSubsystem Controller", GetPIDController());
	GetPIDController()->SetInputRange(2.36, 4.05);
	GetPIDController()->SetOutputRange(-1.0, 0.75);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PID
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	shooterArmPot = RobotMap::shooterArmshooterArmPot;
	shooterArmMotor = RobotMap::shooterArmshooterArmMotor;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	_targetAngle = 0.0;
    _onStage2 = false;
    _onStage3 = false;
    _targetPosition = CUSTOM;
	ResetPID();
}
double ShooterArm::ReturnPIDInput()
{
    // Return your input value for the PID loop
    return shooterArmPot->GetAverageVoltage();;
}
void ShooterArm::UsePIDOutput(double output)
{
    //Go from stage 1 to to 2, or from stage 3 to 2 if off target
    if (((_onStage2 == false) && (OnTarget())) ||
        ((_onStage3 == true) && (OnTarget() == false)))
    {
        _onStage2 = true;
        _onStage3 = false;
        PIDController *pid = GetPIDController(); 
        pid->SetPID(_bothStage_P,_stage_2_I,_stage_2_D);
        pid->SetAbsoluteTolerance(fabs(_stage_2_tolerance * VOLTAGE_DEG_SCALAR));
    }
    else if ((_onStage2 == true) && (_onStage3 == false) && (OnTarget()))
    {
        _onStage3 = true;
        PIDController *pid = GetPIDController(); 
        pid->SetPID(_bothStage_P,0.0,_stage_2_D);
        //pid->SetAbsoluteTolerance(fabs(_stage_2_tolerance * VOLTAGE_DEG_SCALAR));
    }
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=OUTPUT
	shooterArmMotor->PIDWrite(output);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=OUTPUT
}
void ShooterArm::InitDefaultCommand()
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
void ShooterArm::SetAngle(float tgtAngle)
{
    _targetPosition = CUSTOM;
    SetTargetAngle(tgtAngle);
}
void ShooterArm::SetTargetAngle(float tgtAngle)
{
    _targetAngle = tgtAngle;
    _onStage2 = false;
    _onStage3 = false;
    PIDController *pid = GetPIDController();
    pid->SetPID(_bothStage_P,_stage_1_I,_stage_1_D);
    GetPIDController()->SetAbsoluteTolerance(fabs(_stage_1_tolerance * VOLTAGE_DEG_SCALAR));
    GetPIDController()->SetSetpoint(DEGREES_TO_VOLTAGE(tgtAngle));
    Enable();
}
void ShooterArm::TestPID(float setpoint,float p, float stage1I, float stage2I, float stage1D,float stage2D, float stage1Tol, float stage2Tol)
{
    //_maxFeedForward = 0.0;
    //float newFeedForward = 0.0;//_maxFeedForward * cos(GetCurrentRadians());
    //GetPIDController()->SetPID(p,i,d, newFeedForward);
    Disable();
    _bothStage_P = p;
    _stage_1_I = stage1I;
    _stage_2_I = stage2I;
    _stage_1_D = stage1D;
    _stage_2_D = stage2D;
    _stage_1_tolerance = stage1Tol;
    _stage_2_tolerance = stage2Tol;
    
    GetPIDController()->SetPID(_bothStage_P,_stage_1_I,_stage_1_D);
    SetAngle(setpoint);
}
void ShooterArm::SetTargetPosition(ShooterArm::ShooterArmPosition position)
{
    if (_targetPosition != position)
    {
        ResetPID();
        
        _targetPosition = position;
        switch (_targetPosition)
        {
            case ShooterArm::LOAD:
                _stage_1_I = 0.04;
                _stage_1_D = 0.5;
                _stage_2_tolerance = 6;
                SetTargetAngle(SHOOTER_ARM_TARGET_LOAD_POSITION);
                break;
            case ShooterArm::EJECT:
                _stage_2_tolerance = 3;
                SetTargetAngle(SHOOTER_ARM_TARGET_EJECT_POSITION);
                break;
            case ShooterArm::LONG_GOAL:
                _stage_2_tolerance = 1.0;
                SetTargetAngle(ARM_TARGET_LONG_GOAL);
                break;
            case ShooterArm::SHORT_GOAL:
                _stage_2_tolerance = 2;
                SetTargetAngle(ARM_TARGET_SHORT_GOAL);
                break;
            case ShooterArm::TRUSS:
                _stage_2_tolerance = 3;
                SetTargetAngle(SHOOTER_ARM_TARGET_TRUSS);
                break;
            case ShooterArm::CATCH:
                _stage_2_tolerance = 6;
                SetTargetAngle(SHOOTER_ARM_TARGET_CATCH);
                break;
            case ShooterArm::AUTONOMOUS_1:
                _stage_2_tolerance = 1.0;
                SetTargetAngle(ARM_TARGET_AUTONOMOUS_1);
                break;
            case ShooterArm::AUTONOMOUS_2:
                _stage_2_tolerance = 1.0;
                SetTargetAngle(ARM_TARGET_AUTONOMOUS_2);
                break;
            case ShooterArm::AUTONOMOUS_3:
                _stage_2_tolerance = 1.0;
                SetTargetAngle(ARM_TARGET_AUTONOMOUS_3);
                break;
            default:
                SetTargetAngle(ARM_TARGET_LONG_GOAL);
                break;
        }
    }
}
void ShooterArm::ResetPID()
{
    GetPIDController()->Reset();
    _bothStage_P = 0.850;
    _stage_1_I = 0.0;
    _stage_2_I = 0.14;
    _stage_1_D = 0.0;
    _stage_2_D = 4.3;
    _stage_1_tolerance = 10.0;
    _stage_2_tolerance = 3.0;
}
float ShooterArm::GetTargetAngle()
{
    return _targetAngle; 
}
