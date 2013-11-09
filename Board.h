//
//  Board.h
//  Leap_test
//
//  Created by 武井 優樹 on 13/07/28.
//  Copyright (c) 2013年 武井 優樹. All rights reserved.
//

#ifndef __Leap_test__Board__
#define __Leap_test__Board__

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Leap.h"

#endif /* defined(__Leap_test__Board__) */


class Board{
private:
    int Board_id;
    int tapped;
    Leap::Finger tapping_finger;
    double x,y;
    char* key;
    
public:
    Board();
    cv::Ptr<IplImage> init(cv::Ptr<IplImage>,int,double,double);
    cv::Ptr<IplImage> draw_area(cv::Ptr<IplImage>,double,double);
    int get_tapped();
    void set_tapping_finger(Leap::Finger);
    void istap(cv::Ptr<IplImage> image);
    char* get_key();
};