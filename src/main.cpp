#include <iostream> 
#include <chrono> 
// #include <opencv2/opencv.hpp>
// #include "TestClass.h"
#include "Camera.h"
#include "Image.h"
#include "Tracking.h"
#include "Measurement.h"
#include "Robot.h"

#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono; 

int main(int argc, char **argv)
{   
    // ====================================================
    bool DEBUG_FLAG = false;
    bool READ_PARAMS_FLAG = false;
    int OBJ_NUMBERS = 4;
    int DIC_ID = 1;
    int WAIT_TIME = 10;

    const int port = 18005;
    std::string ip_addr = "192.168.2.2";

    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--read_params") {
        READ_PARAMS_FLAG = true;;
        }
        else if (std::string(argv[i]) == "--object_number" && i + 1 < argc) {
        OBJ_NUMBERS = std::stoi(argv[i + 1]);
        }
        else if (std::string(argv[i]) == "--dict_id" && i + 1 < argc) {
        DIC_ID = std::stoi(argv[i + 1]);
        }
        else if (std::string(argv[i]) == "--wait_time" && i + 1 < argc) {
        WAIT_TIME = std::stoi(argv[i + 1]);
        }
        else if (std::string(argv[i]) == "--verbose") {
        DEBUG_FLAG = true;
        }

        else if (std::string(argv[i]) == "--help" || std::string(argv[i]) == "-h") {
        std::cout << argv[0] << " help message!! "
                                << "\n";
       return EXIT_SUCCESS;
     }
   }

    // camera parameters initializing
    CamParams camera_parameters;
    camera_parameters.auto_flag = false;
    camera_parameters.rgb_flag = true;
    camera_parameters.brightness = 13;
    camera_parameters.exposure = 1;
    camera_parameters.shutter = 6;
    camera_parameters.gain = 10;
    camera_parameters.width = 650;
    camera_parameters.hight = 1024;
    camera_parameters.framerate = 30;
    camera_parameters.videomode = VideoMode::FORMAT_RGB8;
    
    JointAngles init_angles {
      20,
      -150,
      -217,
      -156,
      50,
      90,
    };

    JointAngles recv_angles;
    // ====================================================
    // camera start from camera class
    // Camera camera_m(camera_parameters);
    // bool camera_start_flag = camera_m.initCamera();
    // Image *image_m = new Image();
    // Tracking *track_m = new Tracking(DIC_ID, READ_PARAMS_FLAG, OBJ_NUMBERS); 
    // Measurement *measurement_m = new Measurement();
    // auto start = high_resolution_clock::now(); 
    // ====================================================
    using namespace std::this_thread; // sleep_for, sleep_until
    using namespace std::chrono;
    
    Robot kinova_robot(ip_addr, port);

    kinova_robot.RobotConnect();
    kinova_robot.initRobot(init_angles);
    // for (size_t i = 0; i < 10; i++)
    // {
    //   if (i%2 ==0){init_angles.q1 -= 20;}
    //   else{init_angles.q1 += 20;}

    //   kinova_robot.setAngles(init_angles);
    //   sleep_for(milliseconds(1000));
    //   kinova_robot.getAngles(&recv_angles);

    // }

    kinova_robot.RobotDisconnect();
    // ====================================================

    // while (1) 
    // {
    //     camera_m.grabImage();
    //     // image convert from visp to cv from image class 
    //     image_m->convertImage((*camera_m.image_RGB_grabbed)); 
    //     // track aruco from track class
    //     track_m->detetcMarkers(image_m->cvimage, DEBUG_FLAG);
    //     cv::namedWindow("Detected markers", cv::WINDOW_NORMAL );
    //     cv::imshow("Detected markers", track_m->copy_image);

    //     char key = (char)cv::waitKey(WAIT_TIME);
    //     if (key == 27)
    //         break;
    // }

    // the clock stuff
    // auto stop = high_resolution_clock::now(); 
    // auto duration = duration_cast<milliseconds>(stop - start); 
    // cout << duration.count() << " milliseconds" <<  endl; 

    return 0;
}
