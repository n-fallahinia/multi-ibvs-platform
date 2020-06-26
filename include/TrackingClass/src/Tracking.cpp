/* =================================================================================
    Image Class for handeling the image captured by the PointGrey cameras 
    attached to each of the robots. Main objective of this class is to convert visp 
    image in to the MAt format supported by opencv. Ultimatly, aruco tracking or YOLO 
    will be used based of the converted images. 

    UNIVERSITY OF UTAH
    BIOROBOTICS LAB
    Navid Fallahinia
    12/08/2019
=================================================================================*/ 

#include "Tracking.h"

// Tracking default constructor
Tracking::Tracking(){std::cout << "Tracking class initiated" << std::endl;}

// Tracking default constructor with dictionary id 
Tracking::Tracking(int dictionary_id, bool readParameters_flag = false)
{   
    if (readParameters_flag)
        // it is on default mode when the cosntructor is called
        _readParameters_flag = true; 
    try
    { 
        std::cout <<" The selected dictionary aruco is: " << std::endl;
        _dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME(dictionary_id));
        std::cout << "\t" << cv::aruco::PREDEFINED_DICTIONARY_NAME(dictionary_id) << std::endl; // MUST BE FIXED!!!
    }catch(const cv::Exception& e)
    {
        const char* _err_msg = e.what();
        std::cout << "exception caught: " << _err_msg << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

// Tracking destructor
Tracking::~Tracking(){}

// Reading the detector parameters from from the yml file in the include directory
bool Tracking::readDetectorParameters(std::string filename, cv::Ptr<cv::aruco::DetectorParameters> &detectorParameters)
{
    cv::FileStorage fs(filename, cv::FileStorage::READ);
    if(!fs.isOpened())
        return false;
    fs["adaptiveThreshWinSizeMin"] >> detectorParameters->adaptiveThreshWinSizeMin;
    fs["adaptiveThreshWinSizeMax"] >> detectorParameters->adaptiveThreshWinSizeMax;
    fs["adaptiveThreshWinSizeStep"] >> detectorParameters->adaptiveThreshWinSizeStep;
    fs["adaptiveThreshConstant"] >> detectorParameters->adaptiveThreshConstant;
    fs["minMarkerPerimeterRate"] >> detectorParameters->minMarkerPerimeterRate;
    fs["maxMarkerPerimeterRate"] >> detectorParameters->maxMarkerPerimeterRate;
    fs["polygonalApproxAccuracyRate"] >> detectorParameters->polygonalApproxAccuracyRate;
    fs["minCornerDistanceRate"] >> detectorParameters->minCornerDistanceRate;
    fs["minDistanceToBorder"] >> detectorParameters->minDistanceToBorder;
    fs["minMarkerDistanceRate"] >> detectorParameters->minMarkerDistanceRate;
    fs["cornerRefinementMethod"] >> detectorParameters->cornerRefinementMethod;
    fs["cornerRefinementWinSize"] >> detectorParameters->cornerRefinementWinSize;
    fs["cornerRefinementMaxIterations"] >> detectorParameters->cornerRefinementMaxIterations;
    fs["cornerRefinementMinAccuracy"] >> detectorParameters->cornerRefinementMinAccuracy;
    fs["markerBorderBits"] >> detectorParameters->markerBorderBits;
    fs["perspectiveRemovePixelPerCell"] >> detectorParameters->perspectiveRemovePixelPerCell;
    fs["perspectiveRemoveIgnoredMarginPerCell"] >> detectorParameters->perspectiveRemoveIgnoredMarginPerCell;
    fs["maxErroneousBitsInBorderRate"] >> detectorParameters->maxErroneousBitsInBorderRate;
    fs["minOtsuStdDev"] >> detectorParameters->minOtsuStdDev;
    fs["errorCorrectionRate"] >> detectorParameters->errorCorrectionRate;
    return true;
}

// Setting the detector parameters 
void Tracking::setDetectorParameters(std::string filename)
{   
    if (_readParameters_flag)
    {
        _detectorParameters = cv::aruco::DetectorParameters::create();
        bool readOk = readDetectorParameters(filename, _detectorParameters);
        if(!readOk)
        { 
            std::cerr << "Invalid detector parameters file" << std::endl;
            std::cout <<"\tDetector parameters are set to default!" << std::endl;
            _readParameters_flag = false;
        }
        std::cout <<"Detector parameters are set manually! " << std::endl;
    }
}

void Tracking::findCenters(std::vector<int> markerIds, std::vector<std::vector<cv::Point2f>> markerCorners)
{
    for (size_t idIdx = 0; idIdx < _markerIds.size(); idIdx++)
    {
        std::cout << "\t ID# "<< _markerIds[idIdx] << " : ";
        float x_coordinate = 0;
        float y_coordinate = 0; 
        for (size_t cornerIdx = 0; cornerIdx < 4; cornerIdx++)
        {
            std::cout << _markerCorners[idIdx][cornerIdx].x << "," << _markerCorners[idIdx][cornerIdx].y ;
            x_coordinate =+ _markerCorners[idIdx][cornerIdx].x;
            y_coordinate =+ _markerCorners[idIdx][cornerIdx].y;
            std::cout << " | ";
        }
        std::cout<<""<<std::endl;
        cv::Point2f corner_center(x_coordinate/4,y_coordinate/4); 
        corner_centers.push_back(corner_center);          
    }
    // !!!! this function might need fix if ids are not match with orders !!!
}

void Tracking::drawDetectedMarkers(cv::Mat input_image, bool show_center)
{
    input_image.copyTo(_copy_image);
    if(_markerIds.size() > 0) 
    {
        // draw each detected marker
        cv::aruco::drawDetectedMarkers(_copy_image, _markerCorners, _markerIds);
        // find the corner centers
        findCenters(_markerIds,_markerCorners);
        // draw the centers if flag is true
        if (show_center)
        {
            for (size_t centerIdx = 0; centerIdx < corner_centers.size(); centerIdx++)
            {
                 cv::circle(input_image, corner_centers[centerIdx], 1, cv::Scalar( 0, 0, 255), cv::FILLED);
            }
        }
    }
}

void Tracking::detetcMarkers(cv::Mat input_image, int point_number, bool initial_check)
{  
    if(_readParameters_flag)
        cv::aruco::detectMarkers(input_image, _dictionary, _markerCorners, _markerIds, _detectorParameters);
    else
        cv::aruco::detectMarkers(input_image, _dictionary, _markerCorners, _markerIds);
    if(initial_check)
    {
        std::cout << _markerIds.size() << " points have been found" << std::endl;
        // ERROR HANDELING FOR THE INITIAL CALL !!!!!!!!!!!!!!!!
    }else
    {
        std::cout << _markerIds.size() << " points have been found" << std::endl;
        drawDetectedMarkers(input_image, true);       
    }
}

