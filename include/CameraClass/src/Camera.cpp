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
// using namespace cv2;

Camera::Camera()
// camera constructor
{
    // camera is still off
    cout << "Camera class initiated" << endl;
    numCameras = vpFlyCaptureGrabber::getNumCameras(); // only designed for 2 or 1 cameras
    cout << "Number of cameras detected: " << numCameras << endl;
}

Camera::~Camera()
// camera class deconstructor
{
    // close();
}

// void Camera::Init_Camera()
// {
//     #ifdef VISP_HAVE_FLYCAPTURE
//     // initializing camera setiing
//     // get camera features and modes!! 
//     numCameras = getNumCameras(); // only designed for 2 or 1 cameras
//     if (numCameras>2)
//     {
//         cout << numCameras << " cameras have been detected, Must be less than 3!" << endl;
//         return;
// ;
//     }
//     cout << "Camera connection established.." << endl;
//     cout << "Number of cameras detected: " << numCameras << endl;
//     // cameras connection are ready
//     for(cam=0; cam < numCameras; cam++) 
//     {
//         cam_grabber[cam].setCameraIndex(cam); // Default camera is the first on the bus
//         cam_grabber.getCameraInfo(cout);
//     }
//     #else
//         cout:<< "Flycapture SDK is not installed!! closing the software ...." << endl;
//         return -1;
//         // call the deconstructor
//     #endif
// }