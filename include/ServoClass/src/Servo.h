/* =================================================================================
    ServClass is made based of VISP library to calculate the join speeds cooresponding 
    to the feature movements in the image space. It is supposed to recieve the feature 
    locations in the image spcae and calculate the end-effector/joint velocities.

    UNIVERSITY OF UTAH
    BIOROBOTICS LAB
    Navid Fallahinia
    12/08/2019
=================================================================================*/ 

/*!
  \file Robot.h
  \brief Kinova robot joint controller
*/

#ifndef SERVO_H_
#define SERVO_H_

#include <iostream>
#include <vector>
#include <string>

// VISP stuff
#include <visp3/core/vpCameraParameters.h>
#include <visp3/visual_features/vpFeatureBuilder.h>
#include <visp3/visual_features/vpFeaturePoint.h>
#include <visp3/vs/vpServo.h>

#if VISP_HAVE_OPENCV_VERSION >= 0x040000
    #include <opencv2/core/core.hpp>
    #include <opencv2/imgproc/imgproc.hpp>
#elif VISP_HAVE_OPENCV_VERSION >= 0x020300
    #include <opencv2/core/core.hpp>
    #include <opencv2/imgproc/imgproc.hpp>
#endif

struct CameraMatrix
{
    double px, py, u0, v0, kud, kdu;
};

struct CameraVelocity
{
    double vx, vy, vz;
    double wx, wy, wz;
};

class Servo
{
private:
    double m_cam_px, m_cam_py, m_cam_u0, m_cam_v0, m_cam_kud, m_cam_kdu;
    double m_des_depth;
    int m_num_points;
    double m_error;

    vpColVector v_c;
    CameraVelocity v;
    std::vector<vpFeaturePoint> p, pd;
    vpCameraParameters cam;
    vpServo task;

public:
    Servo();
    Servo(const CameraMatrix&, int, bool);
    virtual ~Servo();


    void loadCamera();
    void setServo();
    void setDesiredView(const std::vector<vpImagePoint>&);
    void updateFeatures(const std::vector<vpImagePoint>&);
    void setDepth(double);
    double getError();
    CameraVelocity getVelocity();


    static std::unique_ptr<Servo> create(const CameraMatrix &, int, bool);
    // static std::unique_ptr<Servo> create();
};


#endif  // SERVO_H_