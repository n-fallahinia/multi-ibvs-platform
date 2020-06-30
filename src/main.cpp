#include <iostream> 
#include <chrono> 
// #include <opencv2/opencv.hpp>
// #include "TestClass.h"
#include "Camera.h"
#include "Image.h"
#include "Tracking.h"

using namespace std;
using namespace std::chrono; 

int main()
{   
    // ====================================================
    // camera parameters initializing
    CamParams camera_parameters;
    camera_parameters.auto_flag = true;
    camera_parameters.rgb_flag = true;
    camera_parameters.brightness = 0;
    camera_parameters.exposure = 1;
    camera_parameters.shutter = 10;
    camera_parameters.gain = 5;
    camera_parameters.width = 650;
    camera_parameters.hight = 1024;
    camera_parameters.framerate = 30;
    camera_parameters.videomode = VideoMode::FORMAT_RGB8;
    // ====================================================
    // camera start from camera class
    Camera camera_m(camera_parameters);
    bool camera_start_flag = camera_m.initCamera();
    Image *image_m = new Image();
    Tracking *track_m = new Tracking(1, false); 
    // auto start = high_resolution_clock::now(); 
    // ====================================================
    int wait_time = 10;
    while (1) 
    {
        camera_m.grabImage();
        // image convert from visp to cv from image class 
        image_m->convertImage((*camera_m.image_RGB_grabbed)); 
        // track aruco from track class
        track_m->detetcMarkers(image_m->cvimage);
        cv::namedWindow("Detected markers", cv::WINDOW_NORMAL );
        cv::imshow("Detected markers", track_m->copy_image);

        char key = (char)cv::waitKey(wait_time);
        if (key == 27)
            break;
    }

    // the clock stuff
    // auto stop = high_resolution_clock::now(); 
    // auto duration = duration_cast<milliseconds>(stop - start); 
    // cout << duration.count() << " milliseconds" <<  endl; 

    return 0;
}
