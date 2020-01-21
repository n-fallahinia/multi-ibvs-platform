#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <vector> 

#include <visp3/core/vpImage.h>
#include <visp3/gui/vpDisplayX.h>
#include <visp3/io/vpImageIo.h>
#include <visp3/sensor/vpFlyCaptureGrabber.h>

class Camera
{   
    public:
        vector<vpImage<vpRGBa>> image_color_grabbed; // Create a color level image container
        vpImage<unsigned char> image_gray_grabbed; // Create a gray level image container
        
        Camera();
        ~Camera();
        void Init_Camera();

    private:
        vpFlyCaptureGrabber     cam_grabber; // Create a grabber based on FlyCapture SDK third party lib
        unsigned int            cam;
        unsigned int            numCameras;


        float shutter_ms;
        float shutter_new;
        float brightness;
        float brightness_new;
        float gain;
        float gain_new;

};

#endif //CAMERA_H_