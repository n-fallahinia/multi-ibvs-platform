#include <iostream> 
#include <chrono> 
// #include <opencv2/opencv.hpp>
// #include "TestClass.h"
#include "Camera.h"
#include "Image.h"

using namespace std;
using namespace std::chrono; 

int main()
{   
    auto start = high_resolution_clock::now(); 
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
    // camera start
    Camera camera_m(camera_parameters);
    if(camera_m.initCamera()){cout<<"Success1\n";}
    if(camera_m.grabImage()){cout<<"Success2\n";}
    Image image_m((*camera_m.image_RGB_grabbed));
    image_m.convertImage((*camera_m.image_RGB_grabbed));
    // cv::imwrite("image-cv.ppm", image_m.cvimage_list[0]);
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<milliseconds>(stop - start); 
    cout << duration.count() << " milliseconds" <<  endl; 

    return 0;
}
