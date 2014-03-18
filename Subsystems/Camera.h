// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#ifndef CAMERA_H
#define CAMERA_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "Vision/RGBImage.h"
#include "Vision/ColorImage.h"
#include "../jankyTask.h"
//#include "../Math.h"
#define VIEW_ANGLE 49
#define PI 3.141592653
#define MAX_PARTICLES 8
#define RECTANGULARITY_LIMIT 40
#define ASPECT_RATIO_LIMIT 55
#define TAPE_WIDTH_LIMIT 50
#define VERTICAL_SCORE_LIMIT 50
#define LR_SCORE_LIMIT 50
//High Resolution
//#define Y_IMAGE_RES 480
//#define X_IMAGE_RES 640
//#define AREA_MINIMUM 150
//#define HEIGHT_MINIMUM 30
//Low Resolution
#define Y_IMAGE_RES 240
#define X_IMAGE_RES 320
#define X_VIEW_ANGLE 67
#define X_DEGREES_PER_PIXEL (X_VIEW_ANGLE / X_IMAGE_RES)
#define AREA_MINIMUM 60
#define HEIGHT_MINIMUM 20
#define THRESHOLD_HSV 70, 155, 200, 255, 32, 210
/**
 * @author ExampleAuthor
 */
class Camera: public Subsystem, public JankyTask {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	
	AxisCamera *camera;
	volatile float _distance;
	float _minShootingDistance;
	float _maxShootingDistance;
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	Relay* rangeGoodLEDs;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    typedef enum hotGoalSide_enum
    {
      neverLooked,
      notDetected, 
      goalLeft, 
      goalRight
    }hotGoalSide;
    
	Camera();
	void InitDefaultCommand();
	
	void ConnectCamera(){GetCamera();}//This will let us begin connecting to the camera before trying to use it
	void ResetHotGoal(){_detectedSide = neverLooked;}
    void EnableDistanceChecking(){GetCamera();Start();}
    void DisableDistanceChecking(){Pause();}
    float GetDistance(){return _distance;}
    void UpdateRangeLEDs(float _distance);
    void SetIdealRange(float min_distance, float max_distance);
	
	void WriteConfig();
	float DetectDistance();
	
	hotGoalSide GetHotGoal();
	hotGoalSide DetectHotGoal();
	void Run(void);
	
	bool SaveImages(const char *baseName, bool verticalOnly);
	bool SaveImages(const char *baseName, Threshold& th, ParticleFilterCriteria2 *cr, int criteriaCount);
	//Stuff from VisionSample2014:
private:
	AxisCamera *GetCamera();
	ColorImage *GetImage();
	BinaryImage *FilterImage(ColorImage *image, bool verticalOnly = false);
	
    hotGoalSide _detectedSide;
	
	
	//Structure to represent the scores for the various tests used for target identification
	struct Scores {
		double rectangularity;
		double aspectRatioVertical;
		double aspectRatioHorizontal;
	};
	
	struct TargetReport {
		int verticalIndex;
		int horizontalIndex;
		bool Hot;
		double totalScore;
		double leftScore;
		double rightScore;
		double tapeWidthScore;
		double verticalScore;
	};
	
	
	double computeDistance (BinaryImage *image, ParticleAnalysisReport *report); 
	
	double scoreAspectRatio(BinaryImage *image, ParticleAnalysisReport *report, bool vertical);
	
	bool scoreCompare(Scores scores, bool vertical);
	
	double scoreRectangularity(ParticleAnalysisReport *report);
	double ratioToScore(double ratio);
	
	bool hotOrNot(TargetReport target);
	double centerXToScore(ParticleAnalysisReport *report);
    double computeAngle(ParticleAnalysisReport *report);
	
	
};
#endif
