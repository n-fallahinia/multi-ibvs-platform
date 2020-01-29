/* ##########################################################
# Camera Class for handeling the PointGrey cameras attached 
# to each of the robots. 
# 
# by Navid Fallahinia
# BioRobotics Lab
############################################################*/
#include <iostream>
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
    vpFlyCaptureGrabber * cam1 = new vpFlyCaptureGrabber;
    cam_grabber.push_back(*cam1);
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
    for(cam=0; cam < numCameras; cam++) 
    {
        cam_grabber[cam].setCameraIndex(cam); // Default camera is the first on the bus
        cam_grabber[cam].getCameraInfo(cout); // printing camera info
    }
    #else
        cout:<< "Flycapture SDK is not installed!! closing the software ...." << endl;
        return;
        // call the deconstructor
    #endif
}

// void Camera::setImageParameters(float *shutter_ms, float *brightness, float *gain, vector<vpFlyCaptureGrabber> *cam_grabber)
// {// set image parameters manually or trun the automated settings 
    
//     shutter_ms = .setShutter(false, shutter_new); // Turn manual shutter on 
//     cout << "Shutter manual: " << shutter_ms << " ms" << endl;

// }
