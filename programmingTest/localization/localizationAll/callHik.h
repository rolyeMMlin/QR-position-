#ifndef CALLHIK_H_
#define CALLHIK_H_

#include "MvCameraControl.h"
#include <opencv2/opencv.hpp>
using namespace cv;


// initial all cameras and print cameras informations
int listCamera(MV_CC_DEVICE_INFO_LIST& stDeviceList);

// call camera careate handel to capturing images; 
void* callHik(unsigned int nIndex, MV_CC_DEVICE_INFO_LIST& stDeviceList, void* handle);

// capture image
int getImage(void* handle, Mat& img);

// destory the handel;
int destoryCamera(void* handle);

#endif