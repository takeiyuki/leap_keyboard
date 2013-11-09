//
//  Image.cpp
//  Leap_test
//
//  Created by 武井 優樹 on 13/07/27.
//  Copyright (c) 2013年 武井 優樹. All rights reserved.
//

#include "Image.h"

Image::Image(){
    Init();
}

void Image::Init(){
    camera = cvCreateImage(cvSize(640,480), IPL_DEPTH_8U, 3);
    tmp_cam = cvCreateImage(cvSize(640,480), IPL_DEPTH_8U, 3);
    if(!camera)throw std::runtime_error("error:cvCreateImage");
    //cvInitFont(&dfont, CV_FONT_BOLD, 1.5f, 1.5f, 1.5f, 1.5f, CV_AA);
}

cv::Ptr<IplImage> Image::get_camera(){
    return camera;
};

void Image::set_camera(cv::Ptr<IplImage> image){
    camera=image;
    memcpy( tmp_cam->imageData,camera -> imageData, camera->imageSize);
}

void Image::update_window(char* name){
    ::cvCvtColor(camera, camera, CV_RGB2BGR);
    ::cvShowImage(name,camera);
    memcpy(camera -> imageData, tmp_cam->imageData, camera->imageSize);
}

void Image::release_all(){
    
}

void Image::scircle(int x,int y){
    cvCircle(camera, cvPoint(x, y), 10, CV_RGB(255, 255, 255));
}

void Image::leap_to_cv(double x, double y, double z){


}


