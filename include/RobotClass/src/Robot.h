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

// TCP/IP Comm stuff
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

const float joint_error= 1;

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

    Robot(const std::string &ip_addr, int port);
    
    void RobotConnect();
    void RobotDisconnect();

    void initRobot(JointAngles &);
    void getAngles(JointAngles *) const;
    void setAngles(JointAngles *);

    ~Robot();

};

#endif  // ROBOT_H_