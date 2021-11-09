#include <iostream> 
#include <chrono> 
#include <memory>
// #include <opencv2/opencv.hpp>
// #include "TestClass.h"

#include "Camera.h"
#include "Image.h"
#include "Tracking.h"
#include "Measurement.h"
#include "Robot.h"
#include "Servo.h"

#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono; 

int main(int argc, char **argv)
{   
  // some debuging stuff
  bool DEBUG_FLAG = true;
  bool READ_PARAMS_FLAG = false;
  int OBJ_NUMBERS = 4;
  int DIC_ID = 1;
  int WAIT_TIME = 10;

  // flag stuff
  bool camera_start_flag;
  bool opt_adaptive_gain = false;
  bool servo_started = false;
  bool send_velocities;
  bool init_view_set = false;
  bool final_quit = false;
  bool use_aruco = false;

  const std::string &cv_first_text = "Press space to continue";
  char userAnswer;

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
  
  // robot setting stuff
  JointAngles init_angles {-20, -155, -217, -156, 50, 90,};
  JointAngles recv_angles;
  const int port = 18006;
  std::string ip_addr = "192.168.2.3";

  // camera setting stuff
  CameraMatrix intrinsic{3003.4345, 3016.6290, 377.9395, 543.5611, 0.04177, 0.04134};
  const double des_depth = 5; 

  // args parser  
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

  // ====================================================
  // creat a camera capture object
  Camera m_camera(camera_parameters);
  camera_start_flag = m_camera.initCamera();
  
  // Image manipulation object
  std::unique_ptr<Image> p_image = Image::create();
  
  // Tracker class
  std::unique_ptr<Tracking> p_tracker = Tracking::create(DIC_ID);
  
  // creat the robot
  std::unique_ptr<Robot> p_robot = Robot::create(ip_addr, port);

  // start the visual servoing controller
  std::unique_ptr<Servo> p_servo = Servo::create(intrinsic, OBJ_NUMBERS, opt_adaptive_gain);

  // Init the cv tracker
  cv::Ptr<cv::Tracker> tracker;
  tracker = cv::TrackerMIL::create();

  // ====================================================
  // first loop to get the robot to the init position
  // also check for the initial view of the fingers

  std::cout << " ========= Initializing the Robot ========= "<< std::endl;
  try {
    // set the robot connection
    // p_robot->RobotConnect();
    // p_robot->initRobot(init_angles);

    p_servo->loadCamera();
    p_servo->setDepth(des_depth);

    cv::namedWindow("ROI selector", cv::WINDOW_NORMAL );

    while (!init_view_set){

      m_camera.grabImage();
      p_image->convertImage((*m_camera.image_RGB_grabbed));
      // track aruco from track class
      if (use_aruco){
        p_tracker->detetcMarkers(p_image->cvimage, DEBUG_FLAG);
            
        cv::putText(p_tracker->copy_image, cv_first_text, cv::Point(0, p_tracker->copy_image.rows - 20), 
              cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(225, 0, 0), 2);

        cv::imshow("ROI selector", p_tracker->copy_image);

        char key = (char)cv::waitKey(WAIT_TIME);
        if (key == 32){
          init_view_set = true;

          // count the number of features
          int c_size = p_tracker->corner_centers.size();
          std::vector<vpImagePoint> des_corners(c_size);

          // build the desired corner vector
          for (size_t i = 0; i < c_size; i++){
            des_corners[i] = vpImagePoint(p_tracker->corner_centers[i].x,
                                p_tracker->corner_centers[i].y);
          }
          // setup the desired view
          p_servo->setDesiredView(des_corners);
          std::cout << " Desired view saved "<< std::endl;
        }
        if (key == 27) {
          throw std::invalid_argument( "no feature selected" );
          break;
        }
    }//end of use_aruco

    else{
      cv::Rect2d roi = cv::selectROI(p_image->cvimage);
      // top_ left -> bottom_left
      cv::Point2d p1 (roi.x - roi.width/2, roi.y - roi.height/2);
      cv::Point2d p2 (roi.x + roi.width/2, roi.y - roi.height/2);
      cv::Point2d p3 (roi.x + roi.width/2, roi.y + roi.height/2);
      cv::Point2d p4 (roi.x - roi.width/2, roi.y + roi.height/2);

      std::vector<vpImagePoint> des_corners(OBJ_NUMBERS);
      // build the desired corner vector
      des_corners[0] = vpImagePoint(p1.x, p1.y);
      des_corners[1] = vpImagePoint(p2.x, p2.y);
      des_corners[2] = vpImagePoint(p3.x, p3.y);
      des_corners[3] = vpImagePoint(p4.x, p4.y);

      // init the tracker
      tracker->init(p_image->cvimage, roi);

      init_view_set = true;
    }

    }// end of the init while loop
      cv::destroyAllWindows();
  }
  catch(const vpException &e) {
    std::cout << "ViSP exception: " << e.what() << std::endl;
    std::cout << "Disconnect the robot " << std::endl;
    p_robot->RobotDisconnect();
    return EXIT_FAILURE;
  }
  catch(const std::exception &e) {
    std::cout << "Kinova connection exception: " << e.what() << std::endl;
    p_robot->RobotDisconnect();
    return EXIT_FAILURE;
  }
  // ====================================================
  // second loop for visual servoing
  for (;;) {
    std::cout << "Ready to start? (y/n) " << std::endl;
    std::cin >> userAnswer;
    if (userAnswer == 'y' || userAnswer == 'Y')
      break;
  }
  std::cout << " ========= Starting the visual servoing ========= "<< std::endl;
  
  servo_started = false;
  send_velocities = false;
  CameraVelocity v_c;
  static double t_init_servo = vpTime::measureTimeMs();
  std::vector<vpImagePoint> traj_corners; // to keep track of the corners traj

  cv::namedWindow("Camera View", cv::WINDOW_NORMAL );

  while (!final_quit){

    double t_start = vpTime::measureTimeMs();
    static bool first_time = true;

    m_camera.grabImage();
    p_image->convertImage((*m_camera.image_RGB_grabbed));

    if (use_aruco){
      // track aruco from track class
      p_tracker->detetcMarkers(p_image->cvimage, false);
    }
    else{
      // update the corner centers from MIL
      // p_tracker->corner_centers
    }

    if (first_time) {
      traj_corners.resize(p_tracker->corner_centers.size());
    }

    // check if all corners found
    if (p_tracker->corner_centers.size() == OBJ_NUMBERS) {
      for (size_t i = 0; i < traj_corners.size(); i++)
      {
        traj_corners[i]= vpImagePoint(p_tracker->corner_centers[i].x,
                               p_tracker->corner_centers[i].y);
      }
      // update the feature space
      p_servo->updateFeatures(traj_corners);
    }

    if (opt_adaptive_gain) {
      if (! servo_started) {
        if (send_velocities) {
          servo_started = true;
      }
        t_init_servo = vpTime::measureTimeMs();
      }
    }
    else {
      v_c = p_servo->getVelocity();  
    }
    double servo_error = p_servo->getError();

    if (DEBUG_FLAG) {
      std::cout << "Vx: " << v_c.vx << " |Vy: " << v_c.vy << " |Vz: " << v_c.vz;
      // std::cout << " Wx: " << v_c.wx << " Wy: " << v_c.wy << " Wz: " << v_c.wz;
      std::cout << " |error: " << servo_error << v_c.wz <<std::endl;
    }
    cv::putText(p_tracker->copy_image, std::to_string(servo_error), cv::Point(0, p_tracker->copy_image.rows - 20), 
      cv::FONT_HERSHEY_DUPLEX, 1.0, CV_RGB(225, 0, 0), 2);

    // ====================================================

    // send velocities
    if(first_time){
      std::cout << "Switch to Velocity Control " << std::endl;
      std::cin >> userAnswer;
      first_time = false;
    }

    p_robot->sendVelocity(&v_c);

    // ====================================================

    cv::imshow("Camera View", p_tracker->copy_image);
    char key = (char)cv::waitKey(WAIT_TIME);
    if (key == 27) {
      final_quit = true;
    }
  }
  cv::destroyWindow("Camera View"); 

    // ====================================================
    // while (init_angles.q1>-30)
    // {
    //   init_angles.q1 -= 1;
    //   kinova_robot.setAngles(&init_angles);
    //   // sleep_for(milliseconds(1000));
    //   kinova_robot.getAngles(&recv_angles);
    //   sleep_for(milliseconds(500));
    //   // std::cout<<"done ";
    //   std::cout<<"q1= sent"<< init_angles.q1<< "    ;q1= recv"<< recv_angles.q1<<std::endl;
    // }
    // ====================================================

    //   servo.setDesiredView(corners);
    return 0;
}
