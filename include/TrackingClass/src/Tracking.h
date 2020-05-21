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

struct MarkerParams
{
    bool auto_flag;
    bool rgb_flag;
    float brightness;
    float gain;
    float exposure; 
    float shutter;
    int width;
    int hight;
    float framerate;
};

class Tracking
{
    cv::Mat _input_image;
    std::vector<int> _markerIds;
    std::vector<std::vector<cv::Point2f>> _markerCorners;
    cv::Ptr<cv::aruco::DetectorParameters> _parameters;
    cv::Ptr<cv::aruco::Dictionary> _dictionary; 
    int _dictionary_id;

public: 
    Tracking();
    Tracking(int _dictionary_id);
    virtual ~Tracking();
    void setParameters();
    bool detetcMarkers(cv::Mat _input_image, cv::Ptr<cv::aruco::Dictionary> _dictionary, cv::Ptr<cv::aruco::DetectorParameters> _parameters);

};

#endif //TRACKING_H_