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

#include "Tracking.h"

// Tracking default constructor
Tracking::Tracking(){std::cout << "Tracking class initiated" << std::endl;}

// Tracking default constructor with dictionary id 
Tracking::Tracking(int _dictionary_id)
{   
    try
    { 
        std::cout <<" The selected dictionary is: " << std::endl;
        _dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME(_dictionary_id));
        std::cout << "\t" << cv::aruco::PREDEFINED_DICTIONARY_NAME(_dictionary_id) << std::endl; // MUST BE FIXED!!!
    }catch(const cv::Exception& e)
    {
        const char* _err_msg = e.what();
        std::cout << "exception caught: " << _err_msg << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

// Tracking destructor
Tracking::~Tracking(){}