#ifndef CAMERA_H
#define CAMERA_H

#include <cstdio>
#include <cstdlib>
#include <sys/time.h>
#include <iostream>
#include <vector> 
#include <string>
// include VISP lib
#include <visp3/core/vpImage.h>
#include <visp3/gui/vpDisplayX.h>
#include <visp3/io/vpImageIo.h>
#include <visp3/sensor/vpFlyCaptureGrabber.h>
// include flycapture lib
#include <FlyCapture2.h>
// include Opencv
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

// Define the video modes
// The default case is MONO8
enum VideoMode 
{ 
    FORMAT_MONO8, FORMAT_RAW8, FORMAT_RGB8, FORMAT_MONO12, FORMAT_RAW12
};

// Define the frame rate speed
// The default case is FORMAT_30
enum FrameRate 
{ 
    FORMAT_15, FORMAT_30, FORMAT_60
};

struct CamParams
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
    VideoMode videomode;
};

class Camera
{   
    std::vector<float> _cam_parameters;
    bool    _auto_flag;
    bool    _rgb_flag;
    float   _shutter;
    float   _brightness;
    float   _gain;
    float   _exposure;
    unsigned int   _frame_rate;
    VideoMode   _videomode;
    unsigned int    _wigth;
    unsigned int    _hight;
    int     _numCameras;
    int     _mode_value;

public:    
    std::vector<vpFlyCaptureGrabber>    *cam_grabber; // Create a grabber based on FlyCapture SDK third party lib
    std::vector<vpImage<vpRGBa>>    *image_RGB_grabbed; // Create a color level image container
    std::vector<vpImage<unsigned char>>     *image_gray_grabbed; // Create a gray level image container
    int  cam_idx;  // will be used in other classes as well
    
    Camera(); // default constructor
    Camera(CamParams &camparams);
    virtual ~Camera();
    bool initCamera();
    bool grabImage();
    bool setAllParameters(float _brightness, float _exposure, float _gain, float _shutter);
    bool setManual2Auto();
    void setBrightness(const float &_brightness);
    void setExposure(const float &_exposure);
    void setGain(const float &_gain);
    void setShutter(const float &_shutter);
    bool setVideoMode(VideoMode &_videomode, unsigned int _wigth, unsigned int _hight);
    bool setFrameRate(unsigned int &_frame_rate);
    bool startCam();
};
#endif //CAMERA_H_