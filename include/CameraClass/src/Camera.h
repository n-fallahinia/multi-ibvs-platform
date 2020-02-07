#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <vector> 

#include <visp3/core/vpImage.h>
#include <visp3/gui/vpDisplayX.h>
#include <visp3/io/vpImageIo.h>
#include <visp3/sensor/vpFlyCaptureGrabber.h>
// include VISP lib
#include <FlyCapture2.h>
// include flycapture lib
#include <opencv2/highgui.hpp>
// #include <opencv2/calib3d.hpp>
// #include <opencv2/aruco/charuco.hpp>
// #include <opencv2/imgproc.hpp>
// include Opencv

#define FORMAT_MONO8  1
#define FORMAT_RAW8   2
#define FORMAT_RGB8   3
#define FORMAT_MONO12 4
#define FORMAT_RAW12  5

static std::vector<vpFlyCaptureGrabber>  cam_grabber(2); // Create a grabber based on FlyCapture SDK third party lib

class Camera
{   
    public:
        // vector<vpImage<vpRGBa>> image_color_grabbed; // Create a color level image container
        vpImage<unsigned char>          image_gray_grabbed; // Create a gray level image container
        int                             numCameras;

        Camera();
        ~Camera();
        void initCamera();
        void setAllParameters(float, float, float, float);
        void setManual2Auto();
        void setBrightness(float);
        void setExposure(float);
        void setGain(float);
        void setShutter(float);
        bool setVideoMode(int, unsigned int, unsigned int);
        void getParameters(float *, float *, float *, float *);
  
    private:
        std::vector<float>              cam_parameters;

        int                             cam_idx;
        bool                            auto_flag;
        float                           shutter;
        float                           brightness;
        float                           gain;
        float                           exposure;
        float                           shutter_new;
        float                           brightness_new;
        float                           gain_new;
        float                           exposure_new;
};

#endif //CAMERA_H_