/* =================================================================================
    Camera Class for handeling the PointGrey cameras attached to each of the robots. 
    This class is designed to be used up to two cameras but can be chnaged to be
    used for any number of cameras simultaneously. This class is an inference from 
    VISP 1.3 which is a wrapper class from flycapture 2.0, That's why both 
    flycapture and Visp are included. Grabbed images are a vector of vpImage object. 
    Conversion to cv.mat object is impelemented in the image class. 

    UNIVERSITY OF UTAH
    BIOROBOTICS LAB
    Navid Fallahinia
    12/08/2019
=================================================================================*/ 

#include "Camera.h"

using namespace std;

// camera default constructor
Camera::Camera(){}

// camera constructor with params argument
Camera::Camera(CamParams &camparams) 
: _auto_flag(camparams.auto_flag), _rgb_flag(camparams.rgb_flag), _brightness(camparams.brightness), _gain(camparams.gain), _exposure(camparams.exposure),
    _shutter(camparams.shutter), _wigth(camparams.width), _hight(camparams.hight), _frame_rate(camparams.framerate), _videomode(camparams.videomode)
{
    cout << "Camera class initiated" << endl;
    #ifdef VISP_HAVE_FLYCAPTURE
        _numCameras =  vpFlyCaptureGrabber::getNumCameras(); // only designed for 2 or 1 cameras
        cout << "Number of cameras detected: " << _numCameras << endl; // number of camera printed
        cam_grabber = new vector<vpFlyCaptureGrabber> (_numCameras);
        if (_rgb_flag)
        {
            image_RGB_grabbed = new vector<vpImage<vpRGBa>> (_numCameras);
        }
        else
        {
            image_gray_grabbed = new vector<vpImage<unsigned char>> (_numCameras);

        }
    #else // if Flycapture is not installed terminate the class
        cout<< "Flycapture SDK is not installed!! closing the software ...." << endl;
        _Exit();
    #endif
}

// camera class destructor
Camera::~Camera()
{
    delete cam_grabber;
     if (_rgb_flag)
    {
        delete image_RGB_grabbed;
    }
    else 
    {
        delete image_gray_grabbed;
    }
 }

bool Camera::initCamera()
{// initializing camera setiing
    if ( _numCameras == 0 )
    {
        cout<< "No camera found" << endl;
        return(false);
    }
    cout << "Camera connection established..." << endl;
    // get camera features and modes!! 
    for(cam_idx=0; cam_idx < _numCameras; cam_idx++) 
    {
        (*cam_grabber)[cam_idx].setCameraIndex(cam_idx); // Default camera is the first on the bus
        (*cam_grabber)[cam_idx].getCameraInfo(cout); // printing camera info

        if ( !setAllParameters( _brightness, _exposure, _gain, _shutter) )
        {   
            cout << "Camera parameter setting FAILED at cam#" << cam_idx << "\n";
            return(false);
        } // set the image settings
        if ( !setVideoMode(_videomode, _wigth, _hight))
        {
            cout << "Camera video mode setting FAILED at cam#" << cam_idx << "\n";
            return(false);
        }// set the video mode 

        if ( !setFrameRate(_frame_rate) )
        {
            cout << "Camera framerate setting FAILED at cam#" << cam_idx << "\n";
            return(false);
        }// set the framerate 

        if ( !startCam() ) // if true the grabImage will be called next
        {
            cout << "Camera connection FAILED at cam#" << cam_idx << "\n";
            return(false);
        }// start camera 

        return(true); //after all return true
    }//cam_idx
}//initCamera

bool Camera::grabImage(){
    for( cam_idx=0; cam_idx < _numCameras; cam_idx++ ) 
    {   
        if (_rgb_flag) 
        {
            try
            {  
                (*cam_grabber)[cam_idx].acquire((*image_RGB_grabbed)[cam_idx]);
                // cout << "Image size : " << (*image_RGB_grabbed)[cam_idx].getWidth() << " " << (*image_RGB_grabbed)[cam_idx].getHeight() << endl;
                return(true);
            }catch(const vpException &e)
            {
                cout << "FAILED to acquire new rgb frame " << e.getStringMessage() << '\n';
                return(false);
            }
        }else
        {
            try
            {  
                (*cam_grabber)[cam_idx].acquire((*image_gray_grabbed)[cam_idx]);
                // cout << "Image size : " << (*image_gray_grabbed)[cam_idx].getWidth() << " " << (*image_RGB_grabbed)[cam_idx].getHeight() << endl;
                return(true);
            }catch(const vpException &e)
            {
                cout << "FAILED to acquire new gray frame " << e.getStringMessage() << '\n';
                return(false);
            }
        }           
    }
    return(true); //after all return true
}

bool Camera::setAllParameters(float brightness, float exposure, float gain, float shutter)
{// set all the image parameters 

    if (!_auto_flag){
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
        (*cam_grabber)[cam_idx].setGain(_auto_flag); // Turn auto gain on
        cout << "\tGain auto at : " << (*cam_grabber)[cam_idx].getGain() << "\n";
        (*cam_grabber)[cam_idx].setShutter(_auto_flag); // Turn auto shutter on
        cout << "\tShutter auto  : " << (*cam_grabber)[cam_idx].getShutter() << "\n";
        (*cam_grabber)[cam_idx].setBrightness(_auto_flag); // Turn auto brightness on
        cout << "\tBrightness auto  : " << (*cam_grabber)[cam_idx].getBrightness() << "\n";
        (*cam_grabber)[cam_idx].setExposure(true, _auto_flag); // Turn auto exposures on
        cout << "\tExposure auto  : " << (*cam_grabber)[cam_idx].getExposure() << endl;
        return(true);
    } catch (const vpException &e) { // if catches any exception from setFuncs
        cout << "failed to start auto settings" << e.getStringMessage() <<endl;
        return (false);
    }//try 
}//setManual2Auto

void Camera::setBrightness (const float &brightness)
{
   (*cam_grabber)[cam_idx].setBrightness(_auto_flag, brightness); // Turn manual brightness on
    cout << "\tBrightness manual: " << (*cam_grabber)[cam_idx].getBrightness() << endl;
}//setBrightness

void Camera::setExposure(const float &exposure)
{
    (*cam_grabber)[cam_idx].setExposure(true, _auto_flag, exposure); // Turn manual exposure on 
    cout << "\tExposure manual: " << (*cam_grabber)[cam_idx].getExposure() << endl;
}//setExposure

void Camera::setGain(const float &gain)
{
    (*cam_grabber)[cam_idx].setGain(_auto_flag, gain); // Turn manual brightness on to 2%
    cout << "\tGain manual: " << (*cam_grabber)[cam_idx].getGain() << endl;
}//setGain

void Camera::setShutter(const float &shutter)
{
    (*cam_grabber)[cam_idx].setShutter(_auto_flag, shutter); // Turn manual brightness on to 2%
    cout << "\tShutter manual: " << (*cam_grabber)[cam_idx].getShutter() << endl;
}//setShutter

bool Camera::setVideoMode(VideoMode &_videomode, unsigned int _wigth, unsigned int _hight)
{
    try{ 
        switch( _videomode )        
        // setFormat7VideoMode throws an exception checking for that
        {
            case FORMAT_MONO8:
                // PIXEL_FORMAT_MONO8 mode
                (*cam_grabber)[cam_idx].setFormat7VideoMode(FlyCapture2::MODE_0, 
                                                            FlyCapture2::PIXEL_FORMAT_MONO8, _wigth, _hight);
                cout << "\tSeleced video mode is FORMAT_MONO8" <<endl;
                break;
            case FORMAT_RAW8:
                // PIXEL_FORMAT_RAW8 mode
                (*cam_grabber)[cam_idx].setFormat7VideoMode(FlyCapture2::MODE_0, 
                                                            FlyCapture2::PIXEL_FORMAT_RAW8, _wigth, _hight);
                cout << "\tSeleced video mode is FORMAT_RAW8" <<endl;                                          
                break;
            case FORMAT_RGB8:
                // PIXEL_FORMAT_RGB8 mode
                (*cam_grabber)[cam_idx].setFormat7VideoMode(FlyCapture2::MODE_0, 
                                                            FlyCapture2::PIXEL_FORMAT_RGB8, _wigth, _hight);
                cout << "\tSeleced video mode is FORMAT_RGB8" <<endl; 
                break;
            case FORMAT_MONO12:
                // PIXEL_FORMAT_MONO12 mode
                (*cam_grabber)[cam_idx].setFormat7VideoMode(FlyCapture2::MODE_0, 
                                                            FlyCapture2::PIXEL_FORMAT_MONO12, _wigth, _hight);
                cout << "\tSeleced video mode is FORMAT_MONO12" <<endl; 
                break;
            case FORMAT_RAW12:
                // PIXEL_FORMAT_RAW12 mode
                (*cam_grabber)[cam_idx].setFormat7VideoMode(FlyCapture2::MODE_0, 
                                                            FlyCapture2::PIXEL_FORMAT_RAW12, _wigth, _hight);
                cout << "\tSeleced video mode is FORMAT_RAW12" <<endl; 
                break;
        }
        // return true if there is no exception and one case
        return (true); // one mode is selected
    } catch (...) { // if catches any exception from setFormat7VideoMode
        cout << "\tSeleced video mode is not supported" <<endl;
        return (false);
    }//try 
}//setVideoMode

bool Camera::setFrameRate(unsigned int  &_frame_rate)
{
    try{ 
        cout << "\tframerate is set to "<< (*cam_grabber)[cam_idx].setFrameRate(_frame_rate) <<endl;
        // return true if there is no exception and one case
        return (true); // framerate is selected
    } catch (...) { // if catches any exception from setFrameRate
        cout << "\tSeleced framerate is not supported" <<endl;
        return (false);
    }//try 
}//setFrameRate

bool Camera::startCam(){
    try{ 
        (*cam_grabber)[cam_idx].connect();  
        (*cam_grabber)[cam_idx].startCapture();
        cout << "camera #" << cam_idx << " started \n";
        return (true); // camera is connected
    } catch (const vpException &e) { // if catches any exception from connect
        cout << "failed to start image capturing at camera #" << cam_idx << e.getStringMessage() <<endl;
        return (false);
    }//try 
}//startCam

// ##################################################################################
// ??????????????????????? NEXT to be done is image write ??????????????.
// ??????????????????????? also refrencing the image ??????????
// ##################################################################################