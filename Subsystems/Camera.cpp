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
#include "../Robot.h"
#include "stdio.h"
Threshold threshold(THRESHOLD_HSV); //HSV threshold criteria, ranges are in that order ie. Hue is 60-100
ParticleFilterCriteria2 criteria[] =
    { { IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false } }; //Particle filter criteria, used to filter out small particles
ParticleFilterCriteria2 vertCriteria[] =
    {
            { IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false } ,
#ifdef IS_ROTATED_90_DEG
            { IMAQ_MT_BOUNDING_RECT_WIDTH, HEIGHT_MINIMUM, 65535, false, false }}; //Particle filter criteria, used to filter out small particles
#else
            { IMAQ_MT_BOUNDING_RECT_HEIGHT, HEIGHT_MINIMUM, 65535, false, false }}; //Particle filter criteria, used to filter out small particles
#endif
Camera::Camera() :
    Subsystem("Camera"),
    JankyTask("DistanceCalc", 200) //Set the task priority to 200, a lower priority than the default 101
{
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	rangeGoodLEDs = RobotMap::camerarangeGoodLEDs;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    _detectedSide = neverLooked;
//    camera = &AxisCamera::GetInstance("10.24.74.11");
    camera = (AxisCamera *) 0;
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
    GetCamera();
    camera->WriteBrightness(5);
    camera->WriteColorLevel(50);
    camera->WriteCompression(50);
    camera->WriteExposureControl(AxisCamera::kExposure_Automatic);
    camera->WriteMaxFPS(5);
    camera->WriteResolution(AxisCamera::kResolution_320x240);
    camera->WriteWhiteBalance(AxisCamera::kWhiteBalance_FixedFlourescent1);
}
Camera::hotGoalSide Camera::GetHotGoal()
{
    if (_detectedSide == neverLooked)
        DetectHotGoal();
    
    return _detectedSide;
}
void Camera::Run(void)
{
    if (camera->IsFreshImage())
    {
        float distance = DetectDistance();
		_distance = distance;
        UpdateRangeLEDs(distance);
    }
}
float Camera::DetectDistance()
{
    BinaryImage *filteredImage;
    //Get an image
    ColorImage *image = GetImage();
    
    //Check to make sure the image isn't null (i.e. the pointer points to nothing)
    if ((image == (ColorImage *)0))
    {
        return -1.0;
    }
    //printf("distance image found \n");    
    //Filter the image
    filteredImage = FilterImage(image, true);
    //Delete the ColorImage from memory, we only need the filtered image now
    delete image;
    
    //Check to make sure the filtered image is not null
    if (filteredImage == (void *)0)
        return -1.0;
    
    //Analyze the filtered image
    vector<ParticleAnalysisReport>* reports = 
            filteredImage->GetOrderedParticleAnalysisReports();
    
    //Check to make sure the reports are valid
    if (reports == (void *)0)
    {
        delete filteredImage; //Delete the filtered image before returning
        return -1.0;
    }
    
    Scores *scores;
    int bestTargetIndex = -1;   //Initialize this to -1, because the 0'th particle could be the best
    double bestTargetScore = 0;
    double distance = 0.0;
    //printf("Report count: %d\n",reports->size());
    
    //Check to see if any particles were found
    if (reports->size() > 0)
    {
        scores = new Scores[reports->size()]; //Because we create memory here, we need to delete it before we leave the function
        //Iterate through each particle report, scoring it and determining whether it is a target or not
        for (unsigned int i = 0; i < MAX_PARTICLES && i < reports->size(); i++)
        {
            //Get the i'th particle report
            ParticleAnalysisReport *report = &(reports->at(i));
            //If the report is not null, analyze it
            if (report != (void *)0)
            {
                //printf("scoring particle %d\n",i);
                //Compute a score to indicate how rectangular the particle is
                scores[i].rectangularity = scoreRectangularity(report);
                //Compute a score on how close we are to the ideal aspect ratio for a vertical target
                scores[i].aspectRatioVertical = scoreAspectRatio(filteredImage, report, true);
                
                //Compute a score for how close to the center of the image the target is (this is specific to the distance routine for 2014)
                double centerednessScore = centerXToScore(report);
                
                //Add the scores
                double totalScore = scores[i].aspectRatioVertical + scores[i].rectangularity + centerednessScore;
                
                //printf("particle: %d is a Horizontal Target centerX: %d centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
                //printf("Scores rect: %f ARvert: %f \n", scores[i].rectangularity, scores[i].aspectRatioVertical);
    
                //Check to see if this particle's score is the best one so far (find the best particle that looks like the vertical target)
                if ((totalScore > bestTargetScore) && (scoreCompare(scores[i], true)))
                {
                    bestTargetScore = totalScore;
                    bestTargetIndex = i;
                }
            }
        }
   
        //If we have a bestTarget (remember, we initialize this to -1 above)
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
            //printf("compute distance\n");
            
            //Compute the distance between the camera and the vision target
            double visionTargetDistance = computeDistance(filteredImage,&(reports->at(bestTargetIndex))); //Hypotenuse of our triangle
            //printf("computed distance:%f\n",visionTargetDistance);
            
            //Compute the angle of the vision target from the center of the camera
            double visionTargetAngle = computeAngle(&(reports->at(bestTargetIndex)));
            //printf("computed angle:%f\n",visionTargetAngle);
            
            //Using the distance and angle to the vision target, we can compute the distance to the wall
            distance = cos(visionTargetAngle * (PI/180)) * visionTargetDistance;//Compute the distance 
        }
        delete scores;  //Delete the scores object we created above
    }
    
    delete filteredImage; //Delete the filtered image before we return
    //reports->clear();//If we have memory leaks, this will be the first thing to try, but the destructor SHOULD take care of the contents
    delete reports;
    
    //printf("Detected Distance: %f \n",distance);
    return distance;
}
 
Camera::hotGoalSide Camera::DetectHotGoal()
{
    BinaryImage *filteredImage;
    //Get an image
    ColorImage *image = GetImage();
    
    //Check to make sure the image isn't null (i.e. the pointer points to nothing)
    if ((image == (ColorImage *)0))
    {
        return neverLooked;
    }
    
    //printf("hot image found \n");
    //Filter the image
    filteredImage = FilterImage(image);   
    //Delete the ColorImage from memory, we only need the filtered image now
    delete image;
    
    //Check to make sure the filtered image is not null
    if (filteredImage == (void *)0)
        return neverLooked;
    //Analyze the filtered image
    vector<ParticleAnalysisReport>* reports = 
            filteredImage->GetOrderedParticleAnalysisReports();
    //Check to make sure the reports are valid
    if (reports == (void *)0)
    {
        delete filteredImage;
        return neverLooked;
    }
    
    Scores *scores;
    TargetReport bestTarget;
    int verticalTargets[MAX_PARTICLES];
    int horizontalTargets[MAX_PARTICLES];
    int verticalTargetCount = 0;
    int horizontalTargetCount = 0;
    //printf("Report count: %d\n",reports->size());
    //Check to see if any particles were found
    if (reports->size() > 0)
    {
        scores = new Scores[reports->size()]; //Because we create memory here, we need to delete it before we leave the function
        //Iterate through each particle report, scoring it and determining whether it is a target or not
        for (unsigned int i = 0; i < MAX_PARTICLES && i < reports->size(); i++)
        {
            //Get the i'th particle report
            ParticleAnalysisReport *report = &(reports->at(i));
            
            //Compute a score to indicate how rectangular the particle is
            scores[i].rectangularity = scoreRectangularity(report);
            
            //Compute a score on how close we are to the ideal aspect ratio for a vertical target
            scores[i].aspectRatioVertical = scoreAspectRatio(filteredImage,
                    report, true);
            
            //Compute a score on how close we are to the ideal aspect ratio for a horizontal target
            scores[i].aspectRatioHorizontal = scoreAspectRatio(filteredImage,
                    report, false);
            
            //Check if the particle is a horizontal target
            if (scoreCompare(scores[i], false))
            {
//                printf("particle: %d is a Horizontal Target centerX: %d centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
                
                //Save the index of this particle report/score as a horizontal target; increment the horizontal target count to keep track of how many we have found
                horizontalTargets[horizontalTargetCount++] = i;
            }
            //Else, Check if the particle is a vertical target
            else if (scoreCompare(scores[i], true))
            {
//                printf("particle: %d is a Vertical Target centerX: %d centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
                //Save the index of this particle report/score as a vertical target; increment the vertical target count to keep track of how many we have found
                verticalTargets[verticalTargetCount++] = i;
            }
            //Else, not a target at all, its index isn't saved as a target
            else
            {
//                printf("particle: %d is not a Target centerX: %d centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
            }
//            printf("Scores rect: %f ARvert: %f \n", scores[i].rectangularity, scores[i].aspectRatioVertical);
//            printf("ARhoriz: %f \n", scores[i].aspectRatioHorizontal);
        }
        
        //Zero out scores and set verticalIndex to first target in case there are no horizontal targets
        bestTarget.totalScore = 0;
        bestTarget.leftScore = 0;
        bestTarget.rightScore = 0;
        bestTarget.tapeWidthScore = 0;
        bestTarget.verticalScore = 0;
        //Set initial indexes
        bestTarget.verticalIndex = verticalTargets[0];
        bestTarget.horizontalIndex = horizontalTargets[0];
        
        //Go though every possible combination of vertical and horizontal targets to find the best pairing that looks like a hot goal
        //This is done by putting one for loop inside another. Below, if we have 3 vertical targets, and 4 horizontal targets, we will execute the inner loop 12 times
        //Iterate through the vertical targets (this is our outer loop, indexed by i)
        for (int i = 0; i < verticalTargetCount; i++)
        {
            //Get the i'th verticalTarget 
            // (this is not the same as the i'th particle report, or the i'th score from above,
            //  verticalTargets[i] gives us the index of the particle report for this vertical target)
            ParticleAnalysisReport *verticalReport = &(reports->at(verticalTargets[i]));
            
            //Now iterate through each horizontal target and try to match it with the i'th vertical target (this is our inner loop, indexed by j)
            for (int j = 0; j < horizontalTargetCount; j++)
            {
                //Get the j'th horizontalTarget (as above)
                ParticleAnalysisReport *horizontalReport = &(reports->at(horizontalTargets[j]));
                
                double horizWidth, horizHeight, vertWidth, leftScore,
                        rightScore, tapeWidthScore, verticalScore, total;
                
                //Measure equivalent rectangle sides for use in score calculation
                //Get the horizontal target's width by looking at the filtered image
                imaqMeasureParticle(filteredImage->GetImaqImage(),          //This routine takes a special version of the image
                        horizontalReport->particleIndex, 0,                 //Tell the routine the index of the particle
                        IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &horizWidth);    //Indicate what we want to measure the long side of the horizontal particle, and pass a reference to our horizontal width
                //Measure the short side of the horizontal target
                imaqMeasureParticle(filteredImage->GetImaqImage(),
                        horizontalReport->particleIndex, 0,
                        IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &horizHeight);
                
                //Measure the short side of the vertical target
                imaqMeasureParticle(filteredImage->GetImaqImage(),
                        verticalReport->particleIndex, 0,
                        IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &vertWidth);
                
#ifdef IS_ROTATED_90_DEG
                //Determine if the horizontal target is in the expected location to the left of the vertical target
                leftScore
                        = ratioToScore(
                                1.2 * ((verticalReport->boundingRect.top + verticalReport->boundingRect.height)//Left edge of vertical tape
                                        - horizontalReport->center_mass_y)          //center of horizontal tape
                                        / horizWidth);
                //Determine if the horizontal target is in the expected location to the right of the vertical target
                rightScore = ratioToScore(
                        1.2 * (horizontalReport->center_mass_y  //Center horizontal tape
                                - verticalReport->boundingRect.top) //Right edge of vertical tape
                                / horizWidth);
#else
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
                                - verticalReport->boundingRect.width)//Should this minus be plus?? probably not due to order of operations
                                / horizWidth);
                
#endif
                //Determine if the width of the tape on the two targets appears to be the same
                tapeWidthScore = ratioToScore(vertWidth / horizHeight);

#ifdef IS_ROTATED_90_DEG
                //Determine if the vertical location of the horizontal target appears to be correct
                verticalScore = ratioToScore(
                        1 - ((verticalReport->boundingRect.left + verticalReport->boundingRect.width)
                                - horizontalReport->center_mass_x) / (4
                                * horizHeight));
#else
                //Determine if the vertical location of the horizontal target appears to be correct
                verticalScore = ratioToScore(
                        1 - (verticalReport->boundingRect.top
                                - horizontalReport->center_mass_y) / (4
                                * horizHeight));
#endif
                //Initialize the total to either the left score or the right score (whichever is bigger)
                total = leftScore > rightScore ? leftScore : rightScore;    //This (?) is the conditional operator, 
                                                                            //its syntax is _assertion_ ? _trueResponse_ : _falseResponse_
                                                                            //if the assertion is true, it returns the first value after the ?
                                                                            //if the assertion is false, it returns the second value
                                                                        
                //Add the scores for the tapeWidth and the verticalScore we computed above
                total += tapeWidthScore + verticalScore;    //a += b; is equivalent to a = a + b;
                
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
            } //End of the inner loop
        } //End of the outer loop
        //Determine if the best target is a Hot target
        bestTarget.Hot = hotOrNot(bestTarget);
        
        
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
        else
        {
            _detectedSide = notDetected;
        }
 
        delete scores;  //Delete the scores object we created above
    }
    
    delete filteredImage; //Delete the filtered image before we return
    //reports->clear();//If we have memory leaks, this will be the first thing to try, but the destructor SHOULD take care of the contents
    delete reports;
    
//    printf("Detected Side: %d",_detectedSide);
    return _detectedSide;
}
bool Camera::SaveImages(const char *baseName, bool verticalOnly, bool rawOnly)
{
    char fileName[40];
    BinaryImage *filteredImage;
    BinaryImage *convexHullImage;
    
    ColorImage *image = GetImage();
    
    if ((image == (ColorImage *)0))
    {
        return false;
    }    
    sprintf(fileName, "%s_raw.bmp", baseName);
    image->Write(fileName);
    
    if (rawOnly)
    {
        delete image;
        return true;
    }
//    image->Write("test_raw.bmp");
//    BinaryImage *hslImage = image->ThresholdHSL(90, 115,30, 255, 70, 255);
//
//    printf("%d\n",i++);
//    
//    sprintf(fileName, "%s_thresh_hsl.bmp", baseName);
//    hslImage->Write(fileName);
//    printf("%d\n",i++);
////    hslImage->Write("test_thresh_hsl.bmp");
//    
//    convexHullImage = hslImage->ConvexHull(false);
//    printf("%d\n",i++);
//    delete hslImage;
//    printf("%d\n",i++);
//    if (verticalOnly == true)
//        filteredImage = convexHullImage->ParticleFilter(vertCriteria, 2);
//    else
//        filteredImage = convexHullImage->ParticleFilter(criteria, 1);
//
//    printf("%d\n",i++);
//    delete convexHullImage;
//    printf("%d\n",i++);
//    sprintf(fileName, "%s_filter_hsl.bmp", baseName);
//    filteredImage->Write(fileName);
////    filteredImage->Write("test_filter_hsl.bmp");
//    delete filteredImage;
    BinaryImage *hsvImage = image->ThresholdHSV(threshold);
    sprintf(fileName, "%s_thresh_hsv.bmp", baseName);
    filteredImage->Write(fileName);
//    hsvImage->Write("test_thresh_hsv.bmp");
    convexHullImage = hsvImage->ConvexHull(false);
    delete hsvImage;
    if (verticalOnly == true)
        filteredImage = convexHullImage->ParticleFilter(vertCriteria, 2);
    else
        filteredImage = convexHullImage->ParticleFilter(criteria, 1);
    
    delete convexHullImage;
    sprintf(fileName, "%s_filter_hsv.bmp", baseName);
    filteredImage->Write(fileName);
//    filteredImage->Write("test_filter_hsv.bmp");
    delete filteredImage;
    delete image;
    return true;
}
bool Camera::SaveImages(const char *baseName, Threshold& th, ParticleFilterCriteria2 *cr, int criteriaCount)
{
    char fileName[40];
    BinaryImage *filteredImage;
    ColorImage *image = GetImage();
    
    if ((image == (ColorImage *)0))
    {
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
///////////////////////////////////////////////////////////////////////////
//              Private Methods
///////////////////////////////////////////////////////////////////////////
AxisCamera *Camera::GetCamera()
{
    if (camera == (AxisCamera *) 0)
    {
        AxisCamera &camRef = AxisCamera::GetInstance("10.24.74.11");
        camera = &camRef;
    }
    return camera;
}
ColorImage *Camera::GetImage()
{
    ColorImage *colorImage = new ColorImage(IMAQ_IMAGE_HSL);
    GetCamera()->GetImage(colorImage);
    if ((colorImage == (ColorImage *)0) || (colorImage->GetHeight() == 0) || (colorImage->GetWidth() == 0))
    {
        printf("invalid image \n");
        if (colorImage != (ColorImage *)0)
        {
            printf("image height = %d\n image width = %d \n",colorImage->GetHeight(),colorImage->GetWidth());
            delete colorImage;
        }
        
        return (ColorImage *)0;
    }
    return colorImage;
}
BinaryImage *Camera::FilterImage(ColorImage *image, bool verticalOnly)
{
    BinaryImage *thresholdImage = image->ThresholdHSV(threshold);
    BinaryImage *convexHullImage = thresholdImage->ConvexHull(false);
    BinaryImage *filteredImage;
    if (verticalOnly == true)
    {
        filteredImage = convexHullImage->ParticleFilter(vertCriteria, 2);
    }
    else
    {
        filteredImage = convexHullImage->ParticleFilter(criteria, 1);
    }
    
    delete thresholdImage;
    delete convexHullImage;
    
    return filteredImage;
}
double Camera::computeDistance(BinaryImage *image,
        ParticleAnalysisReport *report)
{
    double rectLong, height;
    int targetHeight;
    //using the smaller of the estimated rectangle long side and the bounding rectangle height results in better performance
    //on skewed rectangles
    imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0,
            IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
    targetHeight = 32;
#ifdef IS_ROTATED_90_DEG
    height = min((float) report->boundingRect.width, (float) rectLong);
    return X_IMAGE_RES * targetHeight / (height * 12 * 2 * tan(
                X_VIEW_ANGLE * PI / (180 * 2)));

#else
    height = min((float) report->boundingRect.height, (float) rectLong);
    return Y_IMAGE_RES * targetHeight / (height * 12 * 2 * tan(
                Y_VIEW_ANGLE * PI / (180 * 2)));
#endif
}

double Camera::computeAngle(ParticleAnalysisReport *report)
{
#ifdef IS_ROTATED_90_DEG
    double xCenter = report->center_mass_y - Y_IMAGE_RES;
    return Y_DEGREES_PER_PIXEL * xCenter;
#else
    double xCenter = report->center_mass_x - X_IMAGE_RES;
    return X_DEGREES_PER_PIXEL * xCenter;
#endif
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
    
    printf("RectLong: %f\tRectShort: %f\n",rectLong,rectShort);
    //Divide width by height to measure aspect ratio
#ifdef IS_ROTATED_90_DEG
    if (report->boundingRect.height > report->boundingRect.width)
#else
    if (report->boundingRect.width > report->boundingRect.height)
#endif
    {
        //particle is wider than it is tall, divide long by short
        aspectRatio = ratioToScore(((rectLong / rectShort) / idealAspectRatio));
    }
    else
    {
        //particle is taller than it is wide, divide short by long
        aspectRatio = ratioToScore(((rectShort / rectLong) / idealAspectRatio));
    }
    printf("AR: %f\n",aspectRatio);
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
#ifdef IS_ROTATED_90_DEG
    return 50 * (1 - fabs(report->center_mass_y_normalized));
#else
    return 50 * (1 - fabs(report->center_mass_x_normalized));
#endif

}
void Camera::SetIdealRange(float min_distance, float max_distance)
{
	_maxShootingDistance = max_distance;
	_minShootingDistance = min_distance;
}
void Camera::UpdateRangeLEDs(float _distance)
{

    float minDistance = _minShootingDistance;
    float maxDistance = _maxShootingDistance;
    
    if ((Robot::driveSubsystem->leftEncoder->GetStopped() == false) || (Robot::driveSubsystem->rightEncoder->GetStopped() == false))
    {
        float leftRateFPS = Robot::driveSubsystem->leftEncoder->GetRate();
        float rightRateFPS = Robot::driveSubsystem->rightEncoder->GetRate();
        
        float rate = (leftRateFPS + rightRateFPS) / 2.0f;
        float angleRad = Robot::shooterArm->GetCurrentRadians();
        
        float minRateMultiplier = (cos(angleRad) + 0.25) * 0.25;
        float maxRateMultiplier = (cos(angleRad) + 0.25) * 0.4;
    
        minDistance += (rate * minRateMultiplier);
        maxDistance += (rate * maxRateMultiplier);
    }    
    
    
    //Wheels Gear ratio ~= 17:45, wheel speed = 2.647 of shaft speed
    //Wheel diameter =
    //Exit Velocity = RPM * 2.647 * PI * wheelDia * slippageMultiplier
    //vertical speed = ExitVelocity * sin(angle)
    //horizontal speed = (ExitVelocity * cos(angle)) + rate
    // Then factor in gravity and drag coefficient
    //
    
    ///32ft/s^2 
    
	
	if ((_distance <= maxDistance) && (_distance >= minDistance))
	{
		rangeGoodLEDs->Set(Relay::kForward);//M+ = 12V, M- = GND
//		rangeGoodLEDs->Set(Relay::kOn);//M+ = 12V, M- = 12v
	}
	else
	{
		rangeGoodLEDs->Set(Relay::kOff);
		//rangeGoodLEDs->Set(Relay::kReverse);//M+ = 12V, M- = 12v
	}
}
