/* =================================================================================
    Image Class for handeling the image captured by the PointGrey cameras 
    attached to each of the robots. Main objective of this class is to convert visp 
    image in to the MAt format supported by opencv. Ultimatly, aruco tracking or YOLO 
    will be used based of the converted images. 

    UNIVERSITY OF UTAH
    BIOROBOTICS LAB
    Navid Fallahinia
    12/08/2019
=================================================================================*/ 

#include <iostream>

#include "Measurement.h"
#include <Eigen/Dense>

Measurement::Measurement() {
    std::cout<<"measurement class started"<<std::endl;
}

Measurement::~Measurement() {}

// Process a single measurement
void Measurement::ProcessMeasurement(){}