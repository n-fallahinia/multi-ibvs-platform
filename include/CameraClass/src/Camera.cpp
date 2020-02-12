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
    gain = 10;
    exposure= 0.85; 
    shutter = 25;
    mode_value = 3;
    w = 680; h = 1024;
    frame_rate = 30;
    cout << "Camera class initiated" << endl;
}

Camera::~Camera()
{// camera class deconstructor
}

bool Camera::initCamera()
{// initializing camera setiing
    #ifdef VISP_HAVE_FLYCAPTURE
    // get camera features and modes!! 
    numCameras =  vpFlyCaptureGrabber::getNumCameras(); // only designed for 2 or 1 cameras
    if (numCameras>2)
    {
        cout << numCameras << " cameras have been detected, Must be less than 3!" << endl;
        return (false);
    }
    cout << "Camera connection established..." << endl;
    cout << "Number of cameras detected: " << numCameras << endl; // number of camera printed
    // cameras connection are ready 
    for(cam_idx=0; cam_idx < numCameras; cam_idx++) 
    {
        cam_grabber[cam_idx].setCameraIndex(cam_idx); // Default camera is the first on the bus
        cam_grabber[cam_idx].getCameraInfo(cout); // printing camera info

        if ( !setAllParameters( brightness,exposure, gain, shutter) )
        {   
            cout << "Camera parameter setting FAILED at cam#" << cam_idx << "\n";
            return(false);
        } // set the image settings
        if ( !setVideoMode(mode_value, w, h) )
        {
            cout << "Camera video mode setting FAILED at cam#" << cam_idx << "\n";
            return(false);
        }// set the video mode 
        if ( !setFrameRate(frame_rate) )
        {
            cout << "Camera framerate setting FAILED at cam#" << cam_idx << "\n";
            return(false);
        }// set the framerate 
                

        // ##################################################################################
        // ??????????????????????? NEXT to be done is connect and open ??????????????.
        // ??????????????????????? One function must be made to called start camera ??????????
        // ##################################################################################

        return(true); //after all return true
    }//cam_idx
    #else
        cout:<< "Flycapture SDK is not installed!! closing the software ...." << endl;
        return (false);
        // call the deconstructor
    #endif
}//initCamera

bool Camera::setAllParameters(float &brightness, float &exposure, float &gain, float &shutter)
{// set all the image parameters 

    if (!auto_flag){
    // set the parametrs manually
        cout << "Camera #"<<cam_idx<<" is set to manual settings\n";
        try
        {  
            setBrightness(brightness); 
            setExposure(exposure); 
            setGain(gain); 
            setShutter(shutter);
            return(true);
        }catch(const vpException &e)
        {
            cout << "failed to set the parameters..! " << e.getStringMessage() << '\n';
            return(false);
        }
    }
    else // go to the auto setting
    {
        cout << "Camera #"<<cam_idx<<" is set to auto settings\n";
        if (setManual2Auto()){ // set the parameters based on auto settings
            return(true);
        }
        cout << "Camera #"<<cam_idx<<" failed to auto settings..!\n";
        return(false);
    }
}//setAllParameters

bool Camera::setManual2Auto()
{   try{ 
        // auto_flag = true; NOT SURE ABOUT THIS ONE
        gain_new = cam_grabber[cam_idx].setGain(auto_flag); // Turn auto gain on
        cout << "\tGain auto at : " << gain_new << "\n";
        shutter_new = cam_grabber[cam_idx].setShutter(auto_flag); // Turn auto shutter on
        cout << "\tShutter auto  : " << shutter_new << "\n";
        brightness_new = cam_grabber[cam_idx].setBrightness(auto_flag); // Turn auto brightness on
        cout << "\tBrightness auto  : " << brightness_new << "\n";
        exposure_new = cam_grabber[cam_idx].setExposure(auto_flag, auto_flag); // Turn auto exposures on
        cout << "\tExposure auto  : " << exposure_new << endl;
        return(true);
    } catch (const vpException &e) { // if catches any exception from setFuncs
        cout << "failed to start auto settings" << e.getStringMessage() <<endl;
        return (false);
    }//try 
}//setManual2Auto

void Camera::setBrightness (float brightness)
{
    brightness_new = cam_grabber[cam_idx].setBrightness(auto_flag, brightness); // Turn manual brightness on
    cout << "\tBrightness manual: " << brightness_new << endl;
}//setBrightness

void Camera::setExposure(float exposure)
{
    exposure_new = cam_grabber[cam_idx].setExposure(auto_flag, exposure); // Turn manual exposure on 
    cout << "\tExposure manual: " << exposure_new << endl;
}//setExposure

void Camera::setGain(float gain)
{
    gain_new = cam_grabber[cam_idx].setGain(auto_flag, gain); // Turn manual brightness on to 2%
    cout << "\tGain manual: " << gain_new << endl;
}//setGain

void Camera::setShutter(float shutter)
{
    shutter_new = cam_grabber[cam_idx].setGain(auto_flag, shutter); // Turn manual brightness on to 2%
    cout << "\tShutter manual: " << shutter_new << endl;
}//setShutter

bool Camera::setVideoMode(int mode_value, unsigned int &w, unsigned int &h)
{
    if ( mode_value<1 || mode_value>5 ) // mode value is not in the defined range
    {
        cout << "Seleced video mode is out of range" <<endl;
        return (false);
    }
    try{ 
        switch( mode_value )        
        // setFormat7VideoMode throws an exception checking for that
        {
            case FORMAT_MONO8:
                // PIXEL_FORMAT_MONO8 mode
                cam_grabber[cam_idx].setFormat7VideoMode(FlyCapture2::MODE_7, 
                                                            FlyCapture2::PIXEL_FORMAT_MONO8, w, h);
                cout << "Seleced video mode is FORMAT_MONO8" <<endl;
                break;
            case FORMAT_RAW8:
                // PIXEL_FORMAT_RAW8 mode
                cam_grabber[cam_idx].setFormat7VideoMode(FlyCapture2::MODE_7, 
                                                            FlyCapture2::PIXEL_FORMAT_RAW8, w, h);
                cout << "Seleced video mode is FORMAT_RAW8" <<endl;                                          
                break;
            case FORMAT_RGB8:
                // PIXEL_FORMAT_RGB8 mode
                cam_grabber[cam_idx].setFormat7VideoMode(FlyCapture2::MODE_7, 
                                                            FlyCapture2::PIXEL_FORMAT_RGB8, w, h);
                cout << "Seleced video mode is FORMAT_RGB8" <<endl; 
                break;
            case FORMAT_MONO12:
                // PIXEL_FORMAT_MONO12 mode
                cam_grabber[cam_idx].setFormat7VideoMode(FlyCapture2::MODE_7, 
                                                            FlyCapture2::PIXEL_FORMAT_MONO12, w, h);
                cout << "Seleced video mode is FORMAT_MONO12" <<endl; 
                break;
            case FORMAT_RAW12:
                // PIXEL_FORMAT_RAW12 mode
                cam_grabber[cam_idx].setFormat7VideoMode(FlyCapture2::MODE_7, 
                                                            FlyCapture2::PIXEL_FORMAT_RAW12, w, h);
                cout << "Seleced video mode is FORMAT_RAW12" <<endl; 
                break;
            // return true if there is no exception and one case
            return (true); // one mode is selected
        }
    } catch (...) { // if catches any exception from setFormat7VideoMode
        cout << "Seleced video mode is not supported" <<endl;
        return (false);
    }//try 
}//setVideoMode

bool Camera::setFrameRate(float &frame_rate)
{
    try{ 
        frame_rate = cam_grabber[cam_idx].setFrameRate(frame_rate);  
        cout << "framerate is set to "<< frame_rate <<endl;
        // return true if there is no exception and one case
        return (true); // framerate is selected
    } catch (...) { // if catches any exception from setFrameRate
        cout << "Seleced framerate is not supported" <<endl;
        return (false);
    }//try 
}//setFrameRate
