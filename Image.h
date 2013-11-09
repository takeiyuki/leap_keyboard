//
//  Image.h
//  Leap_test
//
//  Created by 武井 優樹 on 13/07/27.
//  Copyright (c) 2013年 武井 優樹. All rights reserved.
//

#ifndef __Leap_test__Image__
#define __Leap_test__Image__

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#endif /* defined(__Leap_test__Image__) */

class Image{
private:
    CvFont dfont;
    cv::Ptr<IplImage> camera =0;
    cv::Ptr<IplImage> tmp_cam;
    
    
public:
    Image();
    void Init();
    void update_window(char *);
    void release_all();
    cv::Ptr<IplImage> get_camera();
    void scircle(int,int);
    void leap_to_cv(double,double,double);
    void set_camera(cv::Ptr<IplImage>);
};