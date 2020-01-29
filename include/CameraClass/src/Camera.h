#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <vector> 

#include <visp3/core/vpImage.h>
#include <visp3/gui/vpDisplayX.h>
#include <visp3/io/vpImageIo.h>
#include <visp3/sensor/vpFlyCaptureGrabber.h>
// include VISP lib

#include <opencv2/highgui.hpp>
// #include <opencv2/calib3d.hpp>
// #include <opencv2/aruco/charuco.hpp>
// #include <opencv2/imgproc.hpp>
// include Opencv

static std::vector<vpFlyCaptureGrabber>  cam_grabber; // Create a grabber based on FlyCapture SDK third party lib

class Camera
{   
    public:
        // vector<vpImage<vpRGBa>> image_color_grabbed; // Create a color level image container
        vpImage<unsigned char>          image_gray_grabbed; // Create a gray level image container
        int                             numCameras;

        Camera();
        ~Camera();
        void initCamera();
        void setImageParameters(float *, float *, float *);

    private:
        unsigned int                    cam;
        float                           shutter_ms;
        float                           brightness;
        float                           gain;
        bool                            manual_flag;

};

#endif //CAMERA_H_