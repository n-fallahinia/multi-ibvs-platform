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

#include "Image.h"

// image default constructor
Image::Image(){std::cout << "Image class initiated" << std::endl;}

// 
Image::Image(std::vector<vpImage<vpRGBa>> &images_list)
{
    _rgb_flag = true;
    for (auto cam_idx = 0; cam_idx < images_list.size(); cam_idx++)
    {
        _hight.push_back(images_list[cam_idx].getHeight());
        _width.push_back(images_list[cam_idx].getWidth());
        std::cout << "Image from camera #"<< cam_idx <<" size is "<< _hight[cam_idx] <<"*"<< _width[cam_idx] <<std::endl;
    }
}

Image::Image(std::vector<vpImage<unsigned char>> &images_list)
{
    _rgb_flag = false;
    for (auto cam_idx = 0; cam_idx < images_list.size(); cam_idx++)
    {
        _hight.push_back(images_list[cam_idx].getHeight());
        _width.push_back(images_list[cam_idx].getWidth());
        std::cout << "Image from camera #"<< cam_idx <<" size is "<< _hight[cam_idx] <<"*"<< _width[cam_idx] <<std::endl;
    }
}

// image destructor
Image::~Image(){std::cout<<"log::~Image()"<<std::endl;}

void Image::convertImage(std::vector<vpImage<vpRGBa>> &images_list)
{   
    for (auto cam_idx = 0; cam_idx < images_list.size(); cam_idx++)
    {
        vpImageConvert::convert(images_list[cam_idx], cvimage);
        // cvimage_list.push_back(cvimage);
    }          
}

std::unique_ptr<Image> Image::create(){
    
    return std::unique_ptr<Image>(new Image());
}

bool writeImage(vpImage<vpRGBa> image, std::string &filename)
{
    try {
        vpImageIo::write(image, filename);
    } catch (const vpException &e) {
            std::cout << e.getMessage() << std::endl;
    } catch (...) {
            std::cout << "Unsupported image format" << std::endl;
    }
}

unsigned int getImageSize(vpImage<vpRGBa> &image)
{
    unsigned int _size = image.getHeight() * image.getWidth();
    return _size;
}

