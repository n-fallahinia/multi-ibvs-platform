# include "Robot.h"
#include <iostream>
#include<string>

// Robot parametric to build the socket
Robot::Robot(const std::string &ip_addr, int port): 
    m_ip_addr(ip_addr), 
    m_port(port), 
    m_connected(false) { 
        std::cout << "Connecting to " << m_ip_addr << " at " << std::to_string(m_port) <<" ..."; 
        m_socket = socket(AF_INET, SOCK_DGRAM, 0);

        if (m_socket < 0){
            std::cerr<< " failed to creat socket, exiting";
            exit(EXIT_FAILURE);
        }

        struct timeval read_timeout;
        read_timeout.tv_sec = 2;
        read_timeout.tv_usec = 0;

        int sokopt = setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof read_timeout);
        if (m_socket < 0){
            std::cerr<< " failed to set socket option, exiting";
            exit(EXIT_FAILURE);
        }

        std::cout<< "socket created"<< std::endl;
        memset(&m_servaddr, 0, sizeof(m_servaddr)); 
        memset(&m_cliaddr, 0, sizeof(m_cliaddr)); 
    };

// destructor
Robot::~Robot() {std::cout<<"log::~Robot()"<<std::endl;}

void Robot::RobotConnect(){
    // server information
    m_servaddr.sin_family = AF_INET;
    m_servaddr.sin_addr.s_addr = INADDR_ANY;
    m_servaddr.sin_port = htons(m_port);

    // Setup remote address
    m_cliaddr.sin_family = AF_INET;
    m_cliaddr.sin_addr.s_addr = inet_addr(m_ip_addr.c_str());
    m_cliaddr.sin_port = htons(m_port);

    if (bind(m_socket, (const struct sockaddr *) &m_servaddr, sizeof(m_servaddr)) < 0){
        
        close(m_socket);
        std::cerr << "fialed to bind"<<std::endl;
        exit(EXIT_FAILURE);

    }
    // std::cout<<"bind success"<<std::endl;
    m_connected = true;
};

void Robot::RobotDisconnect(){
    if (m_connected == true){
        std::cout <<"closing the stream ...";
        close(m_socket);
        std::cout<<"Done!"<< std::endl;
        m_connected = false;
    }
};

void Robot::initRobot(JointAngles &init_angles){
    if(m_connected == false){
        RobotDisconnect();
        exit(EXIT_FAILURE);
    }

    std::cout<< "moving to the initial location ..."<<std::flush;
    while (!errorConverge(p_current_angles, init_angles))
    {
        // sending to the actual init position
        setAngles(&init_angles);
        getAngles(&p_current_angles);
     }
    std::cout<<" Done!"<<std::endl;
};

void Robot::getAngles(JointAngles *recv_angles) {
    socklen_t sock_addr_size_rec = sizeof(struct sockaddr_in);
    int rec = recvfrom(m_socket, (char *) recv_angles, sizeof(JointAngles), 0, 
                    (struct sockaddr *) &m_cliaddr, &sock_addr_size_rec);
}

void Robot::setAngles(JointAngles* angles){
    socklen_t sock_addr_size_snd = sizeof(struct sockaddr_in);
    int sent = sendto(m_socket, (const char *) angles, sizeof(JointAngles), 0, 
                    (const struct sockaddr *) &m_cliaddr, sock_addr_size_snd);      
};


bool Robot::errorConverge(JointAngles& rec_angles, JointAngles& des_angles){
    if (&rec_angles != nullptr){
        float e1 = std::abs( rec_angles.q1 - des_angles.q1);
        float e2 = std::abs( rec_angles.q2 - des_angles.q2);
        float e3 = std::abs( rec_angles.q3 - des_angles.q3);
        float e4 = std::abs( rec_angles.q4 - des_angles.q4);
        float e5 = std::abs( rec_angles.q5 - des_angles.q5);
        float e6 = std::abs( rec_angles.q6 - des_angles.q6);

        if(e1< joint_error 
        && e2< joint_error
        && e3< joint_error
        && e4< joint_error
        && e5< joint_error
        && e6< joint_error){
            return true;
        }
    }
    else {
        return false;
    }
};


