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
    std::vector<int> _markerIds;
    std::vector<std::vector<cv::Point2f>> _markerCorners;
    cv::Ptr<cv::aruco::Dictionary> _dictionary; 
    cv::Ptr<cv::aruco::DetectorParameters> _detectorParameters;
    bool _readParameters_flag = false;
    bool _detection_success;
    int _desired_point_numbers;

public: 
    std::vector<cv::Point2f> corner_centers;
    cv::Mat copy_image;

    Tracking();
    Tracking(int dictionary_id, bool readParameters_flag = false, int desired_point_numbers = 4);
    virtual ~Tracking();

    bool readDetectorParameters(std::string filename, cv::Ptr<cv::aruco::DetectorParameters> &detectorParameters);
    void setDetectorParameters(std::string filename);
    void detetcMarkers(cv::Mat input_image, bool verbose=false);
    void drawDetectedMarkers(cv::Mat input_image, bool verbose, bool show_center =false);
    void findCenters(std::vector<int> markerIds, std::vector<std::vector<cv::Point2f>> markerCorners, bool verbose);

    static std::unique_ptr<Tracking> create(int dictionary_id);
};

#endif //TRACKING_H_