// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
SpeedController* RobotMap::driveSubsystemleftDrive = NULL;
SpeedController* RobotMap::driveSubsystemrightDrive = NULL;
RobotDrive* RobotMap::driveSubsystemTheDriveTrain = NULL;
Encoder* RobotMap::driveSubsystemleftEncoder = NULL;
Encoder* RobotMap::driveSubsystemrightEncoder = NULL;
Gyro* RobotMap::driveSubsystemdriveGyro = NULL;
AnalogChannel* RobotMap::shooterArmshooterArmPot = NULL;
SpeedController* RobotMap::shooterArmshooterArmMotor = NULL;
AnalogChannel* RobotMap::shooterArmFiveVoltMeasure = NULL;
SpeedController* RobotMap::shooterWheelsleftWheelMotor = NULL;
SpeedController* RobotMap::shooterWheelsrightWheelMotor = NULL;
DigitalInput* RobotMap::shooterWheelsleftWheelDigitalInput = NULL;
DigitalInput* RobotMap::shooterWheelsrightWheelDigitalInput = NULL;
DoubleSolenoid* RobotMap::collectorcollectorLifter = NULL;
SpeedController* RobotMap::collectorrollerMotor = NULL;
DoubleSolenoid* RobotMap::collectorflipperSolenoid = NULL;
DigitalInput* RobotMap::collectorflipperSwitch = NULL;
Relay* RobotMap::camerarangeGoodLEDs = NULL;
DoubleSolenoid* RobotMap::shiftersshiftSolenoid = NULL;
DoubleSolenoid* RobotMap::shooterPistonFiringSolenoid = NULL;
Compressor* RobotMap::compressorSubsystemTheCompressor = NULL;
Relay* RobotMap::compressorSubsystemCompressorTest = NULL;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
void RobotMap::init() {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	LiveWindow* lw = LiveWindow::GetInstance();
	driveSubsystemleftDrive = new Talon(1, 1);
	lw->AddActuator("DriveSubsystem", "leftDrive", (Talon*) driveSubsystemleftDrive);
	
	driveSubsystemrightDrive = new Talon(1, 2);
	lw->AddActuator("DriveSubsystem", "rightDrive", (Talon*) driveSubsystemrightDrive);
	
	driveSubsystemTheDriveTrain = new RobotDrive(driveSubsystemleftDrive, driveSubsystemrightDrive);
	
	driveSubsystemTheDriveTrain->SetSafetyEnabled(true);
        driveSubsystemTheDriveTrain->SetExpiration(0.3);
        driveSubsystemTheDriveTrain->SetSensitivity(0.5);
        driveSubsystemTheDriveTrain->SetMaxOutput(1.0);
        
	driveSubsystemleftEncoder = new Encoder(1, 2, 1, 3, false, Encoder::k4X);
	lw->AddSensor("DriveSubsystem", "leftEncoder", driveSubsystemleftEncoder);
	driveSubsystemleftEncoder->SetDistancePerPulse(0.004188790204786391);
        driveSubsystemleftEncoder->SetPIDSourceParameter(Encoder::kDistance);
        driveSubsystemleftEncoder->Start();
	driveSubsystemrightEncoder = new Encoder(1, 4, 1, 5, true, Encoder::k4X);
	lw->AddSensor("DriveSubsystem", "rightEncoder", driveSubsystemrightEncoder);
	driveSubsystemrightEncoder->SetDistancePerPulse(0.004188790204786391);
        driveSubsystemrightEncoder->SetPIDSourceParameter(Encoder::kDistance);
        driveSubsystemrightEncoder->Start();
	driveSubsystemdriveGyro = new Gyro(1, 2);
	lw->AddSensor("DriveSubsystem", "driveGyro", driveSubsystemdriveGyro);
	driveSubsystemdriveGyro->SetSensitivity(0.007);
	shooterArmshooterArmPot = new AnalogChannel(1, 1);
	lw->AddSensor("ShooterArm", "shooterArmPot", shooterArmshooterArmPot);
	
	shooterArmshooterArmMotor = new Talon(1, 4);
	lw->AddActuator("ShooterArm", "shooterArmMotor", (Talon*) shooterArmshooterArmMotor);
	
	shooterArmFiveVoltMeasure = new AnalogChannel(1, 7);
	lw->AddSensor("ShooterArm", "FiveVoltMeasure", shooterArmFiveVoltMeasure);
	
	shooterWheelsleftWheelMotor = new Talon(1, 3);
	lw->AddActuator("ShooterWheels", "leftWheelMotor", (Talon*) shooterWheelsleftWheelMotor);
	
	shooterWheelsrightWheelMotor = new Talon(1, 5);
	lw->AddActuator("ShooterWheels", "rightWheelMotor", (Talon*) shooterWheelsrightWheelMotor);
	
	shooterWheelsleftWheelDigitalInput = new DigitalInput(1, 7);
	lw->AddSensor("ShooterWheels", "leftWheelDigitalInput", shooterWheelsleftWheelDigitalInput);
	
	shooterWheelsrightWheelDigitalInput = new DigitalInput(1, 6);
	lw->AddSensor("ShooterWheels", "rightWheelDigitalInput", shooterWheelsrightWheelDigitalInput);
	
	collectorcollectorLifter = new DoubleSolenoid(1, 5, 6);      
	
	
	collectorrollerMotor = new Victor(1, 6);
	lw->AddActuator("Collector", "rollerMotor", (Victor*) collectorrollerMotor);
	
	collectorflipperSolenoid = new DoubleSolenoid(1, 7, 8);      
	
	
	collectorflipperSwitch = new DigitalInput(1, 9);
	lw->AddSensor("Collector", "flipperSwitch", collectorflipperSwitch);
	
	camerarangeGoodLEDs = new Relay(1, 2);
	lw->AddActuator("Camera", "rangeGoodLEDs", camerarangeGoodLEDs);
	
	shiftersshiftSolenoid = new DoubleSolenoid(1, 1, 2);      
	
	
	shooterPistonFiringSolenoid = new DoubleSolenoid(1, 3, 4);      
	
	
	compressorSubsystemTheCompressor = new Compressor(1, 1, 1, 1);
	
	
	compressorSubsystemCompressorTest = new Relay(1, 8);
	lw->AddActuator("CompressorSubsystem", "CompressorTest", compressorSubsystemCompressorTest);
	
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    lw->AddActuator("ShooterPiston", "piston", (DoubleSolenoid*) shooterPistonFiringSolenoid);
    lw->AddActuator("Collector", "Lifter", (DoubleSolenoid*) collectorcollectorLifter);
    lw->AddActuator("Shifter", "piston", (DoubleSolenoid*) shiftersshiftSolenoid);
}
