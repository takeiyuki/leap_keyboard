//
//  Board.cpp
//  Leap_test
//
//  Created by 武井 優樹 on 13/07/28.
//  Copyright (c) 2013年 武井 優樹. All rights reserved.
//

#include "Board.h"


Board::Board(){
    //init();
}


cv::Ptr<IplImage> Board::init(cv::Ptr<IplImage> image,int id,double board_x,double board_z){
    Board_id = id;
    tapped = 0;
    //tapping_finger = NULL;
    x = board_x;
    y = board_z;
    key = "a";
    return draw_area(image,x, y);
}

int Board::get_tapped(){
    return tapped;
}

cv::Ptr<IplImage> Board::draw_area(cv::Ptr<IplImage> image,double x, double y){
    cvRectangle(image, cvPoint(x-25, y-25), cvPoint(x+25, y+25), CV_RGB(255, 255, 255));
    return image;
}

void Board::istap(cv::Ptr<IplImage> image){
    tapped = 1;
    cvRectangle(image, cvPoint(x-25, y-25), cvPoint(x+25, y+25), CV_RGB(100, 100, 100),-1);
    
}
/*
bool Board::istap(Leap::Finger finger){
    if(finger.tipVelocity()[1]>300){
        tapped = 1;
        tapping_finger = finger;
        return 1;
    }else if(finger.tipVelocity()[1]<-50){
        tapped = 0;
        //tapping_finger = NULL;
        return 0;
    }else return 0;
}
*/

char* Board::get_key(){
    return key;
}

