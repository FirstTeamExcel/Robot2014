// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#ifndef SHOOTERARM_H
#define SHOOTERARM_H
#include "Commands/PIDSubsystem.h"
#include "WPILib.h"
//Determine these values (note, the spaces here are important)
#define VOLTAGE_AT_MIN_ANGLE (5.0)
#define VOLTAGE_AT_MAX_ANGLE (0.0)
#define VOLTAGE_RANGE (VOLTAGE_AT_MAX_ANGLE - VOLTAGE_AT_MIN_ANGLE)
#define DEGREES_ROTATION (340.0)
#define RADIANS_ROTATION (DEGREES_ROTATION * (3.1415926 / 180))
#define DEG_VOLTAGE_SCALAR (DEGREES_ROTATION / VOLTAGE_RANGE)   //DegreesPerVolt
#define RAD_VOLTAGE_SCALAR (RADIANS_ROTATION / VOLTAGE_RANGE)   //DegreesPerVolt
#define VOLTAGE_DEG_SCALAR (VOLTAGE_RANGE / DEGREES_ROTATION)
#define VOLTAGE_AT_ZERO_DEGREES 3.985
#define VOLTAGE_TO_DEGREES(volts) ((volts - VOLTAGE_AT_ZERO_DEGREES) * DEG_VOLTAGE_SCALAR) //Volts * DegreesPerVolt = Degrees
#define VOLTAGE_TO_RADIANS(volts) ((volts - VOLTAGE_AT_ZERO_DEGREES) * RAD_VOLTAGE_SCALAR)
#define DEGREES_TO_VOLTAGE(degrees) ((degrees * VOLTAGE_DEG_SCALAR) + VOLTAGE_AT_ZERO_DEGREES)
#define DEGREES_DEADZONE 0.5
#define BROWNOUT_VOLTAGE 6.5
//^^This is a macro, parenthesis immediately after the define allow you to pass a value into the macro and use it
/**
 *
 *
 * @author ExampleAuthor
 */
class ShooterArm: public PIDSubsystem {
public:
    typedef enum {LOAD,EJECT,LONG_GOAL,SHORT_GOAL,TRUSS,AUTONOMOUS_1,AUTONOMOUS_2,AUTONOMOUS_3,AUTONOMOUS_CLOSE, CATCH, CUSTOM}ShooterArmPosition;
 private:
	float _targetAngle;
	float _bothStage_P;
    float _stage_1_I;
    float _stage_2_I;
    float _stage_1_D;
    float _stage_2_D;
    float _stage_1_tolerance;
    float _stage_2_tolerance;
    bool _onStage2;
    bool _onStage3;
    float _voltageTarget;
    ShooterArmPosition _targetPosition;
	
    void SetTargetAngle(float tgtAngle);
 public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	AnalogChannel* shooterArmPot;
	SpeedController* shooterArmMotor;
	AnalogChannel* voltageMonitor;
	AnalogChannel* fiveVoltMeasure;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	ShooterArm();
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	void InitDefaultCommand();
//	static const double TARGET = 1.0;
//	static const double TRUSS = 3.0;
//	static const double PASS = 0.0;
	
	float GetCurrentAngle(){return (VOLTAGE_TO_DEGREES(GetPotVoltage()));}
	float GetCurrentRadians(){return (VOLTAGE_TO_RADIANS(GetPotVoltage()));}
    bool IsStage2(){return _onStage2;}
	bool IsOnTarget(){return (_onStage2 && OnTarget());}
	void SetAngle(float tgtAngle);
	void TestPID(float setpoint,float p, float stage1I, float stage2I, float stage1D,float stage2D, float stage1Tol, float stage2Tol);
	void ShooterArm::ResetPID();
	
//	float GetBatteryVoltage(){return DriverStation::GetInstance()->GetBatteryVoltage();}
	float GetPotVoltage(){
//	        float voltScalar = 5.0 / fiveVoltMeasure->GetAverageVoltage();
//	        return shooterArmPot->GetAverageVoltage() * voltScalar;

	        return shooterArmPot->GetAverageVoltage();
	}
//	void SetTargetPosition(typedef enum position);
	
	
	ShooterArmPosition GetTargetPosition(){return _targetPosition;}
	void SetTargetPosition(ShooterArmPosition position);
	
	PIDController* GetThePIDController(){return GetPIDController();}
	float GetTargetAngle();
 private:
};
#endif
