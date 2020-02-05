/* ##########################################################
# Camera Class for handeling the PointGrey cameras attached 
# to each of the robots. 
# 
# by Navid Fallahinia
# BioRobotics Lab
############################################################*/
#include<iostream>
#include <vector> 

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "Camera.h"
// include the camera class header file
using namespace std;

Camera::Camera()
{// camera constructor
    // camera is still off 
    auto_flag = true; //starts with auto setting at initilizing
    brightness = 16;  // initial values for the cam parameters
    gain = 3;
    exposure= 5; 
    shutter = 15;
    cout << "Camera class initiated" << endl;
}

Camera::~Camera()
{// camera class deconstructor
}

void Camera::initCamera()
{// initializing camera setiing
    #ifdef VISP_HAVE_FLYCAPTURE
    // get camera features and modes!! 
    numCameras =  vpFlyCaptureGrabber::getNumCameras(); // only designed for 2 or 1 cameras
    if (numCameras>2)
    {
        cout << numCameras << " cameras have been detected, Must be less than 3!" << endl;
        return;
    }
    cout << "Camera connection established..." << endl;
    cout << "Number of cameras detected: " << numCameras << endl; // number of camera printed
    // cameras connection are ready 
    for(cam_idx=0; cam_idx < numCameras; cam_idx++) 
    {
        cam_grabber[cam_idx].setCameraIndex(cam_idx); // Default camera is the first on the bus
        cam_grabber[cam_idx].getCameraInfo(cout); // printing camera info
        setAllParameters(brightness,exposure, gain, shutter); // set the image settings 
        // ##################################################################################
        // ??????????????????????? NEXT to be done is framemode and video mode ??????????????
        // ##################################################################################
    }
    #else
        cout:<< "Flycapture SDK is not installed!! closing the software ...." << endl;
        return;
        // call the deconstructor
    #endif
}

void Camera::setAllParameters(float brightness, float exposure, float gain, float shutter)
{// set all the image parameters 
    if (!auto_flag){
        // set the parametrs manually
        cout << "Camera #"<<cam_idx<<" is set to automatic settings\n";
        setBrightness(brightness); 
        setExposure(exposure); 
        setGain(gain); 
        setShutter(shutter);
    }
    else // go to the auto setting
    {
        cout << "Camera #"<<cam_idx<<" is set to manual settings\n";
        setManual2Auto(); // set the parameters based on auto settings
    }
}

void Camera::setManual2Auto()
{   
    auto_flag = true;
    gain_new = cam_grabber[cam_idx].setGain(auto_flag); // Turn auto gain on
    cout << "\tGain auto  : " << gain_new << "\n";
    shutter_new = cam_grabber[cam_idx].setShutter(auto_flag); // Turn auto shutter on
    cout << "\tShutter auto  : " << shutter_new << "\n";
    brightness_new = cam_grabber[cam_idx].setBrightness(auto_flag); // Turn auto brightness on
    cout << "\tBrightness auto  : " << brightness_new << "\n";
    exposure_new = cam_grabber[cam_idx].setExposure(auto_flag, auto_flag); // Turn auto exposures on
    cout << "\tExposure auto  : " << exposure_new << endl;
}

void Camera::setBrightness (float brightness)
{
    brightness_new = cam_grabber[cam_idx].setBrightness(auto_flag, brightness); // Turn manual brightness on
    cout << "Brightness manual: " << brightness_new << " %" << endl;
}

void Camera::setExposure(float exposure)
{
    exposure_new = cam_grabber[cam_idx].setExposure(auto_flag, exposure); // Turn manual exposure on 
    cout << "Exposure manual: " << exposure_new << " %" << endl;
}

void Camera::setGain(float gain)
{
    gain_new = cam_grabber[cam_idx].setGain(auto_flag, gain); // Turn manual brightness on to 2%
    cout << "Gain manual: " << gain_new << " %" << endl;
}

void Camera::setShutter(float shutter)
{
    shutter_new = cam_grabber[cam_idx].setGain(auto_flag, shutter); // Turn manual brightness on to 2%
    cout << "Shutter manual: " << shutter_new << " %" << endl;
}
