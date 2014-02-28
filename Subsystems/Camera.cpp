// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Camera.h"
#include "../Robotmap.h"
#include "../Math.h"
#include "stdio.h"
Threshold *threshold;//(105, 137, 230, 255, 133, 183); //HSV threshold criteria, ranges are in that order ie. Hue is 60-100
ParticleFilterCriteria2 criteria[] =
    { { IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false } }; //Particle filter criteria, used to filter out small particles
ParticleFilterCriteria2 vertCriteria[] =
    {
            { IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false } ,
            { IMAQ_MT_BOUNDING_RECT_HEIGHT, HEIGHT_MINIMUM, 65535, false, false }  }; //Particle filter criteria, used to filter out small particles
Camera::Camera() :
    Subsystem("Camera"),JankyTask()
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    _detectedSide = neverLooked;
//    camera = &AxisCamera::GetInstance("10.24.74.11");
            
    threshold = new Threshold(105, 137, 230, 255, 133, 183);
}
void Camera::InitDefaultCommand()
{
    // Set the default command for a subsystem here.
    //SetDefaultCommand(new MySpecialCommand());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
void Camera::WriteConfig()
{
    camera->WriteBrightness(5);
    camera->WriteColorLevel(50);
    camera->WriteCompression(50);
    camera->WriteExposureControl(AxisCamera::kExposure_Automatic);
    camera->WriteMaxFPS(5);
    camera->WriteResolution(AxisCamera::kResolution_320x240);
    camera->WriteWhiteBalance(AxisCamera::kWhiteBalance_FixedFlourescent1);
}
void Camera::EnableDistanceChecking()
{
    Start();
}
void Camera::DisableDistanceChecking()
{
    Pause();
}
void Camera::Run(void)
{
    if (camera->IsFreshImage())
    {
        float distance = DetectDistance();
        if (distance > 0.0)
            _distance = distance;
    }
}
void Camera::TakePicture( const char *fileName)
{
    RGBImage *image;
    camera->GetImage(image);
    if ((image == (RGBImage *)0) || (image->GetHeight() == 0) || (image->GetWidth() == 0))
    {
        if (image != (RGBImage *)0)
            delete image;
        
        return;
    }
    image->Write(fileName);
}
float Camera::GetDistance()
{
    return _distance;
}
vector<ParticleAnalysisReport>* AnalyzeImage(RGBImage *image,
        BinaryImage *filteredImage, bool verticalOnly = false)
{
    BinaryImage *thresholdImage = image->ThresholdHSV(*threshold);
    BinaryImage *convexHullImage = thresholdImage->ConvexHull(false);
    if (verticalOnly == true)
        filteredImage = convexHullImage->ParticleFilter(vertCriteria, 2);
    else
        filteredImage = convexHullImage->ParticleFilter(criteria, 1);
    
    vector<ParticleAnalysisReport>* reports =
            filteredImage->GetOrderedParticleAnalysisReports();
    delete thresholdImage;
    delete convexHullImage;
    
    return reports;
}
float Camera::DetectDistance()
{
    RGBImage *image;
    BinaryImage *filteredImage;
    camera->GetImage(image);
    
    if ((image == (RGBImage *)0) || (image->GetHeight() == 0) || (image->GetWidth() == 0))
    {
        if (image != (RGBImage *)0)
            delete image;
        
        return -1.0;
    }
        
    
    vector<ParticleAnalysisReport>* reports =
            AnalyzeImage(image, filteredImage);
    delete image;
    
    Scores *scores;
    
    //Iterate through each particle, scoring it and determining whether it is a target or not
    int bestTargetIndex = -1;
    double bestTargetScore = 0;
    double distance = 0.0;
    if (reports->size() > 0)
    {
        scores = new Scores[reports->size()];
        for (unsigned int i = 0; i < MAX_PARTICLES && i < reports->size(); i++)
        {
            ParticleAnalysisReport *report = &(reports->at(i));
            
            //Score each particle on rectangularity and aspect ratio
            scores[i].rectangularity = scoreRectangularity(report);
            scores[i].aspectRatioVertical = scoreAspectRatio(filteredImage,
                    report, true);
            double totalScore = scores[i].aspectRatioVertical + scores[i].rectangularity + centerXToScore(report);
            
            if ((totalScore > bestTargetScore) && (scoreCompare(scores[i], true)))
            {
                bestTargetScore = totalScore;
                bestTargetIndex = i;
            }
        }
   
        if (bestTargetIndex >= 0)
        {
            if (bestTargetIndex >= 0)
            {
                //reflectiveTape->  | | 
                //                    \      |       
                //                     \     |
                //                      \    |
                // visionTargetDistance->\   |  <-distance (to where we are actually aiming)
                //                        \  |
                //                         \ |
                //                          \|  <- visionTargetAngle
                //                           0 <- camera, facing directly ahead of the robot
                
                double visionTargetDistance = computeDistance(filteredImage,&(reports->at(bestTargetIndex))); //Hypotenuse of our triangle
                double visionTargetAngle = computeAngle(&(reports->at(bestTargetIndex)));
                
                //We use the distance to the vision target, and the angle to the vision target to determine the distance to the wall
                distance = cos(visionTargetAngle * (PI/180)) * visionTargetDistance;//Compute the distance 
            }
        }
        delete scores;
    }
    delete filteredImage;
    //reports->clear();?
    delete reports;
    return distance;
}
Camera::hotGoalSide Camera::DetectHotGoal()
{
    RGBImage *image;
    BinaryImage *filteredImage;
    camera->GetImage(image);
    if ((image == (RGBImage *)0) || (image->GetWidth() == 0) || (image->GetHeight() == 0))
    {
//        if (image != (RGBImage *)0)
//            delete image;
            
        return neverLooked;
    }
    
    vector<ParticleAnalysisReport>* reports =
            AnalyzeImage(image, filteredImage);
    //delete image;
    
    Scores *scores;
    TargetReport bestTarget;
    int verticalTargets[MAX_PARTICLES];
    int horizontalTargets[MAX_PARTICLES];
    int verticalTargetCount, horizontalTargetCount;
    
    
    
    verticalTargetCount = horizontalTargetCount = 0;
    //Iterate through each particle, scoring it and determining whether it is a target or not
    if (reports->size() > 0)
    {
        scores = new Scores[reports->size()];
        for (unsigned int i = 0; i < MAX_PARTICLES && i < reports->size(); i++)
        {
            ParticleAnalysisReport *report = &(reports->at(i));
            
            //Score each particle on rectangularity and aspect ratio
            scores[i].rectangularity = scoreRectangularity(report);
            scores[i].aspectRatioVertical = scoreAspectRatio(filteredImage,
                    report, true);
            scores[i].aspectRatioHorizontal = scoreAspectRatio(filteredImage,
                    report, false);
            
            //Check if the particle is a horizontal target, if not, check if it's a vertical target
            if (scoreCompare(scores[i], false))
            {
                // printf("particle: %d is a Horizontal Target centerX: %d centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
                horizontalTargets[horizontalTargetCount++] = i; //Add particle to target array and increment count
            }
            else if (scoreCompare(scores[i], true))
            {
                // printf("particle: %d is a Vertical Target centerX: %d centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
                verticalTargets[verticalTargetCount++] = i; //Add particle to target array and increment count
            }
            else
            {
                // printf("particle: %d is not a Target centerX: %d centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
            }
            // printf("Scores rect: %f ARvert: %f \n", scores[i].rectangularity, scores[i].aspectRatioVertical);
            // printf("ARhoriz: %f \n", scores[i].aspectRatioHorizontal);
        }
        //Zero out scores and set verticalIndex to first target in case there are no horizontal targets
        bestTarget.totalScore = bestTarget.leftScore = bestTarget.rightScore
                = bestTarget.tapeWidthScore = bestTarget.verticalScore = 0;
        bestTarget.verticalIndex = verticalTargets[0];
        for (int i = 0; i < verticalTargetCount; i++)
        {
            ParticleAnalysisReport *verticalReport = &(reports->at(
                    verticalTargets[i]));
            for (int j = 0; j < horizontalTargetCount; j++)
            {
                ParticleAnalysisReport *horizontalReport = &(reports->at(
                        horizontalTargets[j]));
                double horizWidth, horizHeight, vertWidth, leftScore,
                        rightScore, tapeWidthScore, verticalScore, total;
                
                //Measure equivalent rectangle sides for use in score calculation
                imaqMeasureParticle(filteredImage->GetImaqImage(),
                        horizontalReport->particleIndex, 0,
                        IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &horizWidth);
                imaqMeasureParticle(filteredImage->GetImaqImage(),
                        verticalReport->particleIndex, 0,
                        IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &vertWidth);
                imaqMeasureParticle(filteredImage->GetImaqImage(),
                        horizontalReport->particleIndex, 0,
                        IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &horizHeight);
                
                //Determine if the horizontal target is in the expected location to the left of the vertical target
                leftScore
                        = ratioToScore(
                                1.2 * (verticalReport->boundingRect.left
                                        - horizontalReport->center_mass_x)
                                        / horizWidth);
                //Determine if the horizontal target is in the expected location to the right of the vertical target
                rightScore = ratioToScore(
                        1.2 * (horizontalReport->center_mass_x
                                - verticalReport->boundingRect.left
                                - verticalReport->boundingRect.width)
                                / horizWidth);
                //Determine if the width of the tape on the two targets appears to be the same
                tapeWidthScore = ratioToScore(vertWidth / horizHeight);
                //Determine if the vertical location of the horizontal target appears to be correct
                verticalScore = ratioToScore(
                        1 - (verticalReport->boundingRect.top
                                - horizontalReport->center_mass_y) / (4
                                * horizHeight));
                total = leftScore > rightScore ? leftScore : rightScore;
                total += tapeWidthScore + verticalScore;
                
                //If the target is the best detected so far store the information about it
                if (total > bestTarget.totalScore)
                {
                    bestTarget.horizontalIndex = horizontalTargets[j];
                    bestTarget.verticalIndex = verticalTargets[i];
                    bestTarget.totalScore = total;
                    bestTarget.leftScore = leftScore;
                    bestTarget.rightScore = rightScore;
                    bestTarget.tapeWidthScore = tapeWidthScore;
                    bestTarget.verticalScore = verticalScore;
                }
            }
            //Determine if the best target is a Hot target
            bestTarget.Hot = hotOrNot(bestTarget);
        }
        
        if (verticalTargetCount > 0)
        {
            if (bestTarget.Hot)
            {
                if (bestTarget.leftScore > bestTarget.rightScore)
                {
                    _detectedSide = goalLeft;
                }
                else
                {
                    _detectedSide = goalRight;
                }
            }
            else
            {
                _detectedSide = notDetected;
            }
        }
        //delete scores;
    }
    //delete filteredImage;
//    reports->clear();?
    //delete reports;
    return _detectedSide;
}
Camera::hotGoalSide Camera::GetHotGoal()
{
    if (_detectedSide == neverLooked)
        DetectHotGoal();
    
    return _detectedSide;
}
bool Camera::SaveImages(const char *baseName, bool verticalOnly)
{
    RGBImage *image;
    BinaryImage *filteredImage;
    char fileName[40];
    camera->GetImage(image);
    
    if ((image == (RGBImage *)0) || (image->GetWidth() == 0) || (image->GetHeight() == 0))
    {
        if (image != (RGBImage *)0)
            delete image;
            
        return false;
    }
    
//    sprintf(fileName, "%s_raw.bmp", baseName);
//    image->Write(fileName);
    image->Write("test_raw.bmp");
    BinaryImage *thresholdImage = image->ThresholdHSV(*threshold);
    
//    sprintf(fileName, "%s_thresh.bmp", baseName);
//    thresholdImage->Write(fileName);
    thresholdImage->Write("test_thresh.bmp");
    
    BinaryImage *convexHullImage = thresholdImage->ConvexHull(false);
    if (verticalOnly == true)
        filteredImage = convexHullImage->ParticleFilter(vertCriteria, 2);
    else
        filteredImage = convexHullImage->ParticleFilter(criteria, 1);
    
//    sprintf(fileName, "%s_filter.bmp", baseName);
//    filteredImage->Write(fileName);
    filteredImage->Write("test_filter.bmp");
    
    delete filteredImage;
    delete convexHullImage;
    delete thresholdImage;
    delete image;
    return true;
}
bool Camera::SaveImages(const char *baseName, Threshold& th, ParticleFilterCriteria2 *cr, int criteriaCount)
{
    RGBImage *image;
    BinaryImage *filteredImage;
    char fileName[40];
    camera->GetImage(image);
    
    if ((image == (RGBImage *)0) || (image->GetWidth() == 0) || (image->GetHeight() == 0))
    {
        if (image != (RGBImage *)0)
            delete image;
            
        return false;
    }
    
    sprintf(fileName, "%s_raw.bmp", baseName);
    image->Write(fileName);
    BinaryImage *thresholdImage = image->ThresholdHSV(th);
    
    sprintf(fileName, "%s_thresh.bmp", baseName);
    thresholdImage->Write(fileName);
    
    BinaryImage *convexHullImage = thresholdImage->ConvexHull(false);
    filteredImage = convexHullImage->ParticleFilter(cr, criteriaCount);
    
    sprintf(fileName, "%s_filter.bmp", baseName);
    filteredImage->Write(fileName);
    
    delete filteredImage;
    delete convexHullImage;
    delete thresholdImage;
    delete image;
    return true;
}
double Camera::computeDistance(BinaryImage *image,
        ParticleAnalysisReport *report)
{
    double rectLong, height;
    int targetHeight;
    
    imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0,
            IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
    //using the smaller of the estimated rectangle long side and the bounding rectangle height results in better performance
    //on skewed rectangles
    height = min((float) report->boundingRect.height, (float) rectLong);
    targetHeight = 32;
    
    return Y_IMAGE_RES * targetHeight / (height * 12 * 2 * tan(
            VIEW_ANGLE * PI / (180 * 2)));
}
double Camera::computeAngle(ParticleAnalysisReport *report)
{
    double xCenter = report->center_mass_x - X_IMAGE_RES;
    
    return X_DEGREES_PER_PIXEL * xCenter;
}
/**
 * Computes a score (0-100) comparing the aspect ratio to the ideal aspect ratio for the target. This method uses
 * the equivalent rectangle sides to determine aspect ratio as it performs better as the target gets skewed by moving
 * to the left or right. The equivalent rectangle is the rectangle with sides x and y where particle area= x*y
 * and particle perimeter= 2x+2y
 * 
 * @param image The image containing the particle to score, needed to perform additional measurements
 * @param report The Particle Analysis Report for the particle, used for the width, height, and particle number
 * @param outer Indicates whether the particle aspect ratio should be compared to the ratio for the inner target or the outer
 * @return The aspect ratio score (0-100)
 */
double Camera::scoreAspectRatio(BinaryImage *image,
        ParticleAnalysisReport *report, bool vertical)
{
    double rectLong, rectShort, idealAspectRatio, aspectRatio;
    idealAspectRatio = vertical ? (4.0 / 32) : (23.5 / 4); //Vertical reflector 4" wide x 32" tall, horizontal 23.5" wide x 4" tall
    imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0,
            IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
    imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0,
            IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &rectShort);
    
    //Divide width by height to measure aspect ratio
    if (report->boundingRect.width > report->boundingRect.height)
    {
        //particle is wider than it is tall, divide long by short
        aspectRatio = ratioToScore(((rectLong / rectShort) / idealAspectRatio));
    }
    else
    {
        //particle is taller than it is wide, divide short by long
        aspectRatio = ratioToScore(((rectShort / rectLong) / idealAspectRatio));
    }
    return aspectRatio; //force to be in range 0-100
}
/**
 * Compares scores to defined limits and returns true if the particle appears to be a target
 * 
 * @param scores The structure containing the scores to compare
 * @param vertical True if the particle should be treated as a vertical target, false to treat it as a horizontal target
 * 
 * @return True if the particle meets all limits, false otherwise
 */
bool Camera::scoreCompare(Scores scores, bool vertical)
{
    bool isTarget = true;
    isTarget &= scores.rectangularity > RECTANGULARITY_LIMIT;
    if (vertical)
    {
        isTarget &= scores.aspectRatioVertical > ASPECT_RATIO_LIMIT;
    }
    else
    {
        isTarget &= scores.aspectRatioHorizontal > ASPECT_RATIO_LIMIT;
    }
    return isTarget;
}
/**
 * Computes a score (0-100) estimating how rectangular the particle is by comparing the area of the particle
 * to the area of the bounding box surrounding it. A perfect rectangle would cover the entire bounding box.
 * 
 * @param report The Particle Analysis Report for the particle to score
 * @return The rectangularity score (0-100)
 */
double Camera::scoreRectangularity(ParticleAnalysisReport *report)
{
    if (report->boundingRect.width * report->boundingRect.height != 0)
    {
        return 100 * report->particleArea / (report->boundingRect.width
                * report->boundingRect.height);
    }
    else
    {
        return 0;
    }
}
/**
 * Converts a ratio with ideal value of 1 to a score. The resulting function is piecewise
 * linear going from (0,0) to (1,100) to (2,0) and is 0 for all inputs outside the range 0-2
 */
double Camera::ratioToScore(double ratio)
{
    return (max((float) 0,
            min((float) (100 * (1 - fabs(1 - ratio))), (float) 100.0)));
}
bool Camera::hotOrNot(TargetReport target)
{
    bool isHot = true;
    
    isHot &= target.tapeWidthScore >= TAPE_WIDTH_LIMIT;
    isHot &= target.verticalScore >= VERTICAL_SCORE_LIMIT;
    isHot &= (target.leftScore > LR_SCORE_LIMIT) | (target.rightScore
            > LR_SCORE_LIMIT);
    
    return isHot;
}
double Camera::centerXToScore(ParticleAnalysisReport *report)
{
    return 50 * (1 - fabs(report->center_mass_x_normalized));
}
//
//void Camera::Test()
//{
//  Scores *scores;
//  TargetReport target;
//  int verticalTargets[MAX_PARTICLES];
//  int horizontalTargets[MAX_PARTICLES];
//  int verticalTargetCount, horizontalTargetCount;
//  Threshold threshold(105, 137, 230, 255, 133, 183);  //HSV threshold criteria, ranges are in that order ie. Hue is 60-100
//  ParticleFilterCriteria2 criteria[] = 
//  {IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false};  //Particle filter criteria, used to filter out small particles
//  AxisCamera &camera = AxisCamera::GetInstance(); //To use the Axis camera uncomment this line
//  
//  while (IsAutonomous() && IsEnabled()) 
//  {
//    ColorImage *image;
//    BinaryImage *thresholdImage = image->ThresholdHSV(threshold);
//    BinaryImage *convexHullIMage = thresholdImage->ConvexHull(false);
//    BinaryImage *filtredImage = convexHullIMage->ParticleFilter(criteria, 1);
//  
//    vector<ParticleAnalysisReport>* reports = filteredImage->GetOrderedParticleAnalysisReports();
//    
//    if(reports->size() > 0)
//      {
//        scores = new Scores[reports->size()];
//        for (unsigned int i = 0; i < MAX_PARTICLES && i < reports->size(); i++) {
//               ParticleAnalysisReport *report = &(reports->at(i));
//                                            
//               //Score each particle on rectangularity and aspect ratio
//               scores[i].rectangularity = scoreRectangularity(report);
//               scores[i].aspectRatioVertical = scoreAspectRatio(filteredImage, report, true);
//               scores[i].aspectRatioHorizontal = scoreAspectRatio(filteredImage, report, false);                       
//                                            
//               //Check if the particle is a horizontal target, if not, check if it's a vertical target
//               if(scoreCompare(scores[i], false))
//               {
//                   printf("particle: %d  is a Horizontal Target centerX: %d  centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
//                   horizontalTargets[horizontalTargetCount++] = i; //Add particle to target array and increment count
//               } else if (scoreCompare(scores[i], true)) {
//                   printf("particle: %d  is a Vertical Target centerX: %d  centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
//                   verticalTargets[verticalTargetCount++] = i;  //Add particle to target array and increment count
//               } else {
//                   printf("particle: %d  is not a Target centerX: %d  centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
//               }
//        printf("Scores rect: %f  ARvert: %f \n", scores[i].rectangularity, scores[i].aspectRatioVertical);
//        printf("ARhoriz: %f  \n", scores[i].aspectRatioHorizontal);     
//        }
//  
//        //Zero out scores and set verticalIndex to first target in case there are no horizontal targets
//        target.totalScore = target.leftScore = target.rightScore = target.tapeWidthScore = target.verticalScore = 0;
//        target.verticalIndex = verticalTargets[0];
//        for (int i = 0; i < verticalTargetCount; i++)
//        {
//            ParticleAnalysisReport *verticalReport = &(reports->at(verticalTargets[i]));
//            for (int j = 0; j < horizontalTargetCount; j++)
//              {
//                ParticleAnalysisReport *horizontalReport = &(reports->at(horizontalTargets[j]));
//                double horizWidth, horizHeight, vertWidth, leftScore, rightScore, tapeWidthScore, verticalScore, total;
//            
//                //Measure equivalent rectangle sides for use in score calculation
//                imaqMeasureParticle(filteredImage->GetImaqImage(), horizontalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &horizWidth);
//                imaqMeasureParticle(filteredImage->GetImaqImage(), verticalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &vertWidth);
//                imaqMeasureParticle(filteredImage->GetImaqImage(), horizontalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &horizHeight);
//                                                    
//                //Determine if the horizontal target is in the expected location to the left of the vertical target
//                leftScore = ratioToScore(1.2*(verticalReport->boundingRect.left - horizontalReport->center_mass_x)/horizWidth);
//                //Determine if the horizontal target is in the expected location to the right of the  vertical target
//                rightScore = ratioToScore(1.2*(horizontalReport->center_mass_x - verticalReport->boundingRect.left - verticalReport->boundingRect.width)/horizWidth);
//                //Determine if the width of the tape on the two targets appears to be the same
//                tapeWidthScore = ratioToScore(vertWidth/horizHeight);
//                //Determine if the vertical location of the horizontal target appears to be correct
//                verticalScore = ratioToScore(1-(verticalReport->boundingRect.top - horizontalReport->center_mass_y)/(4*horizHeight));
//                total = leftScore > rightScore ? leftScore:rightScore;
//                total += tapeWidthScore + verticalScore;
//                                                    
//                //If the target is the best detected so far store the information about it
//                if(total > target.totalScore)
//                  {
//                    target.horizontalIndex = horizontalTargets[j];
//                    target.verticalIndex = verticalTargets[i];
//                    target.totalScore = total;
//                    target.leftScore = leftScore;
//                    target.rightScore = rightScore;
//                    target.tapeWidthScore = tapeWidthScore;
//                    target.verticalScore = verticalScore;
//                  }
//              }
//            //Determine if the best target is a Hot target
//            target.Hot = hotOrNot(target);
//        }
//        
//        if(verticalTargetCount > 0)
//          {
//              //Information about the target is contained in the "target" structure
//              //To get measurement information such as sizes or locations use the
//              //horizontal or vertical index to get the particle report as shown below
//              ParticleAnalysisReport *distanceReport = &(reports->at(target.verticalIndex));
//              double distance = computeDistance(filteredImage, distanceReport);
//              if(target.Hot)
//              {
//                  printf("Hot target located \n");
//                  printf("Distance: %f \n", distance);
//              } else {
//                  printf("No hot target present \n");
//                  printf("Distance: %f \n", distance);
//              }
//          }
//        // be sure to delete images after using them
//          delete filteredImage;
//          delete thresholdImage;
//          delete image;
//                  
//        //delete allocated reports and Scores objects also
//          delete scores;
//          delete reports;
//          
//        
//      }
//    ParticleAnalysisReport *report = reports->at(i);
//      //      ParticleAnalysisReport *report = (ParticleAnalysisReport *)(reports->at(i));
//    }
//}
