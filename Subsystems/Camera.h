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
#define AREA_MINIMUM 37
#define HEIGHT_MINIMUM 15



/**
 *
 *
 * @author ExampleAuthor
 */
class Camera: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
//	vector<ParticleAnalysisReport>* AnalyzeImage(RGBImage *image, BinaryImage *filteredImage);
	
	AxisCamera *camera;
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
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
	void WriteConfig();
	
	
	float DetectDistance();
	double ComputeDistance();
	
	hotGoalSide GetHotGoal();
	hotGoalSide DetectHotGoal();
	
	//Stuff from VisionSample2014:
private:

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
	
};
#endif
