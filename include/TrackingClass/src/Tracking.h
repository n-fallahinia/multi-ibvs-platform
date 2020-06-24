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

/*!
  \file Tracking.h
  \brief Track aruco markers on the images
*/

#ifndef TRACKING_H
#define TRACKING_H

#include <cstdlib>
#include <iostream>
#include <vector> 
#include <string>
 
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/aruco.hpp>

class Tracking
{
    cv::Mat _copy_image;
    std::vector<int> _markerIds;
    std::vector<std::vector<cv::Point2f>> _markerCorners;
    cv::Ptr<cv::aruco::Dictionary> _dictionary; 
    cv::Ptr<cv::aruco::DetectorParameters> _detectorParameters;
    bool _readParameters_flag = false;

public: 
    Tracking();
    Tracking(int dictionary_id, bool readParameters_flag);
    virtual ~Tracking();
    bool readDetectorParameters(std::string filename, cv::Ptr<cv::aruco::DetectorParameters> &detectorParameters);
    void setDetectorParameters(std::string filename);
    void detetcMarkers(cv::Mat input_image, int point_number =4, bool initial_check= false);
    void drawDetectedMarkers(cv::Mat input_image, bool show_center =false);
};

#endif //TRACKING_H_