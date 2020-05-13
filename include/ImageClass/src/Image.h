#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <vector> 

// include VISP for image manipulation
#include <visp3/core/vpImage.h>
#include <visp3/core/vpImageConvert.h>
#include <visp3/io/vpImageIo.h>
 
#if VISP_HAVE_OPENCV_VERSION >= 0x040000
    #include <opencv2/core/core.hpp>
    #include <opencv2/imgproc/imgproc.hpp>
    #include <opencv2/calib3d/calib3d.hpp>
#elif VISP_HAVE_OPENCV_VERSION >= 0x020300
    #include <opencv2/core/core.hpp>
    #include <opencv2/imgproc/imgproc.hpp>
#endif

class Image
{
    std::vector<unsigned int>    _hight;
    std::vector<unsigned int>    _width;
    unsigned int    _image_size;
    bool            _rgb_flag;

public:
    std::vector<cv::Mat> cvimage_list;

    Image();
    Image(std::vector<vpImage<vpRGBa>> &images_list); // probably one with the initial image size!!
    Image(std::vector<vpImage<unsigned char>> &images_list); // probably one with the initial image size!!
    virtual ~Image();

    bool readImage(std::vector<vpImage<vpRGBa>> &images_list);
    bool writeImage(vpImage<vpRGBa> &images_list, std::string &filename);
    void convertImage(std::vector<vpImage<vpRGBa>> &images_list);
    unsigned int getImageSize(vpImage<vpRGBa> &image);
};

#endif //IMAGE_H_