/* =================================================================================
    RobotClass is a TCP/IP connection wrapper for the control SDK on the Windows 
    machine to run the quarc node in Simulink. The class is written to control the
    Kinova Mico2 6DoF robot in joint space.  

    UNIVERSITY OF UTAH
    BIOROBOTICS LAB
    Navid Fallahinia
    12/08/2019
=================================================================================*/ 

/*!
  \file Robot.h
  \brief Kinova robot joint controller
*/


#ifndef ROBOT_H_
#define ROBOT_H_

#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <time.h>
#include <unistd.h> 
#include <sys/time.h>
#include <inttypes.h>
#include <memory>

// TCP/IP Comm stuff
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// Camera Velocity struct
#include <Servo.h>

static const float joint_error= 1;

struct JointAngles
{
    double q1, q2, q3, q4, q5, q6;
};

class Robot {
    bool m_connected;
    JointAngles p_current_angles;

    const int m_port;
    const std::string m_ip_addr;
    int m_socket;
    sockaddr_in m_servaddr, m_cliaddr;

    bool errorConverge(JointAngles&, JointAngles&);

public : 

    Robot();
    Robot(const std::string &, int);
    virtual ~Robot();

    void RobotConnect();
    void RobotDisconnect();
    void initRobot(JointAngles &);
    void getAngles(JointAngles *) const;
    void setAngles(JointAngles *);
    void sendVelocity(CameraVelocity *);

    static std::unique_ptr<Robot> create(const std::string &,int);
};

#endif  // ROBOT_H_