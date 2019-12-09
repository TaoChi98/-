#ifndef TESTFACEAPI_TESTFACEAPI_INCLUDE_ORBE_CAMERA_H 
#define TESTFACEAPI_TESTFACEAPI_INCLUDE_ORBE_CAMERA_H

// 该类为使用奥比中光双目摄像头之用

#include "opencv2\opencv.hpp"
class  OrbeCamera
{
public:
    OrbeCamera();
    ~OrbeCamera();
    int open(cv::Mat &cvRGBImg, cv::Mat &cvDepthImg);
  	
};
#endif