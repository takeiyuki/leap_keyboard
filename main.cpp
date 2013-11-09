/******************************************************************************\
 * Copyright (C) 2012-2013 Leap Motion, Inc. All rights reserved.               *
 * Leap Motion proprietary and confidential. Not for distribution.              *
 * Use subject to the terms of the Leap Motion SDK Agreement available at       *
 * https://developer.leapmotion.com/sdk_agreement, or another agreement         *
 * between Leap Motion and you, your company or other organization.             *
 \******************************************************************************/

#include <iostream>
#include <map>
#include "Leap.h"
#include "Image.h"
#include "Board.h"
using namespace Leap;
using namespace std;

class SampleListener : public Listener {
public:
    virtual void onInit(const Controller&);
    virtual void onConnect(const Controller&);
    virtual void onDisconnect(const Controller&);
    virtual void onExit(const Controller&);
    virtual void onFrame(const Controller&);
    virtual void onFocusGained(const Controller&);
    virtual void onFocusLost(const Controller&);
};

void SampleListener::onInit(const Controller& controller) {
    std::cout << "Initialized" << std::endl;
}

void SampleListener::onConnect(const Controller& controller) {
    std::cout << "Connected" << std::endl;
    controller.enableGesture(Gesture::TYPE_CIRCLE);
    controller.enableGesture(Gesture::TYPE_KEY_TAP);
    controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
    controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onDisconnect(const Controller& controller) {
    //Note: not dispatched when running in a debugger.
    std::cout << "Disconnected" << std::endl;
}

void SampleListener::onExit(const Controller& controller) {
    std::cout << "Exited" << std::endl;
}

//動的確保するようにして、手をいくつでも認識できるようにする
Vector finger_point[10];
int tap_position = -1;
int finger_ct = 0;
HandList hands;

void SampleListener::onFrame(const Controller& controller) {
    // Get the most recent frame and report some basic information
    const Frame frame = controller.frame();
    //frame = controller.frame();
    /*
    std::cout << "Frame id: " << frame.id()
    << ", timestamp: " << frame.timestamp()
    << ", hands: " << frame.hands().count()
    << ", fingers: " << frame.fingers().count()
    << ", tools: " << frame.tools().count()
    << ", gestures: " << frame.gestures().count() << std::endl;
    */
    if (!frame.hands().empty()) {
        
        hands = frame.hands();
        
        /*
        const Hand hand = frame.hands()[0];
        
        // Check if the hand has any fingers
        const FingerList fingers = hand.fingers();
        if (!fingers.empty()) {
            // Calculate the hand's average finger tip position
            Vector avgPos;
            
            //ここで指の位置をとってる
            for (int i = 0; i < (finger_ct = fingers.count()); ++i) {
                //avgPos += fingers[i].tipPosition();
                finger_point[i] = fingers[i].tipPosition();
                //std::cout <<finger_point[0]+100 << std::endl;
            }
            //avgPos /= (float)fingers.count();
            //std::cout << "Hand has " << fingers.count()
            //<< " fingers, average finger tip position" << avgPos << std::endl;
        }
        
        // Get the hand's sphere radius and palm position
        std::cout << "Hand sphere radius: " << hand.sphereRadius()
        << " mm, palm position: " << hand.palmPosition() << std::endl;
        
        // Get the hand's normal vector and direction
        const Vector normal = hand.palmNormal();
        const Vector direction = hand.direction();
        
        // Calculate the hand's pitch, roll, and yaw angles
        std::cout << "Hand pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
        << "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
        << "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;
        */
    }
    
    
    // Get gestures
    const GestureList gestures = frame.gestures();
    for (int g = 0; g < gestures.count(); ++g) {
        Gesture gesture = gestures[g];
        
        switch (gesture.type()) {
                /*
            case Gesture::TYPE_CIRCLE:
            {
                CircleGesture circle = gesture;
                std::string clockwiseness;
                
                if (circle.pointable().direction().angleTo(circle.normal()) <= PI/4) {
                    clockwiseness = "clockwise";
                } else {
                    clockwiseness = "counterclockwise";
                }
                
                // Calculate angle swept since last frame
                float sweptAngle = 0;
                if (circle.state() != Gesture::STATE_START) {
                    CircleGesture previousUpdate = CircleGesture(controller.frame(1).gesture(circle.id()));
                    sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * PI;
                }
                std::cout << "Circle id: " << gesture.id()
                << ", state: " << gesture.state()
                << ", progress: " << circle.progress()
                << ", radius: " << circle.radius()
                << ", angle " << sweptAngle * RAD_TO_DEG
                <<  ", " << clockwiseness << std::endl;
                break;
            }
            case Gesture::TYPE_SWIPE:
            {
                SwipeGesture swipe = gesture;
                std::cout << "Swipe id: " << gesture.id()
                << ", state: " << gesture.state()
                << ", direction: " << swipe.direction()
                << ", speed: " << swipe.speed() << std::endl;
                break;
            }*/
            case Gesture::TYPE_KEY_TAP:
            {
                
                KeyTapGesture tap = gesture;
                /*std::cout << "Key Tap id: " << gesture.id()
                << ", state: " << gesture.state()
                << ", position: " << tap.position()
                << ", direction: " << tap.direction()<< std::endl;
                */
                int tap_x,tap_z;
                
                tap_x = (tap.position()[0]+320)/50;
                tap_z = (tap.position()[2]+75)/50;
                tap_position = tap_x + tap_z*10;
                cout<<"tap_pos:"<<tap_position<<endl;
                break;
            }/*
            case Gesture::TYPE_SCREEN_TAP:
            {
                ScreenTapGesture screentap = gesture;
                std::cout << "Screen Tap id: " << gesture.id()
                << ", state: " << gesture.state()
                << ", position: " << screentap.position()
                << ", direction: " << screentap.direction()<< std::endl;
                break;
            }*/
            default:
                std::cout << "Unknown gesture type." << std::endl;
                break;
        }
    }
    
    if (!frame.hands().empty() /*|| !gestures.empty()*/) {
        //std::cout << std::endl;
    }
}

void SampleListener::onFocusGained(const Controller& controller) {
    std::cout << "Focus Gained" << std::endl;
}

void SampleListener::onFocusLost(const Controller& controller) {
    std::cout << "Focus Lost" << std::endl;
}



int tap_ct=0;
void cvmainloop(){
    Image image;
    Board board[30];
    int tap_list[30]={};
    int tapped_time[30]={};
    
    for(int i=0;i<10;i++){
        for(int k=0;k<3;k++){
            image.set_camera(board[i+k*10].init(image.get_camera(), i+k*10, 50*(i+1), 100+50*(k+1)));
        }
    }
    
    while(1){
        
        
        if(tap_position>-1 && tap_position < 30 && tap_list[tap_position] == 0){
            //board[tap_position].istap(image.get_camera());
            cout<<"key is "<<board[tap_position].get_key()<<endl;
            tap_list[tap_position] = 1;
            tap_position = -1;
        }else tap_position = -1;
        
        for(int i=0;i<10;i++){
            for(int k=0;k<3;k++){
                if(tapped_time[i+k*10] >50){
                    tap_list[i+k*10] = 0;
                    tapped_time[i+k*10] = 0;
                }
                if(tap_list[i+k*10] == 1){
                    board[i+k*10].istap(image.get_camera());
                    tapped_time[i+k*10]++;
                    //cout<<"tapped_time:"<<tapped_time[i+k*10]<<endl;
                }
            }
        }
        
            for(int k=0;k<hands.count();k++){
                const Hand hand = hands[k];
                // Check if the hand has any fingers
                const FingerList fingers = hand.fingers();
                if (!fingers.empty()) {
                    // Calculate the hand's average finger tip position
                    Vector finger_point;
                    
                    //ここで指の位置をとってる
                    for (int i = 0; i < (finger_ct = fingers.count()); ++i) {
                        finger_point = fingers[i].tipPosition();
                        image.scircle(finger_point[0]+340,200+finger_point[2]/*480-finger_point[1]*/);
                        //if(fingers[i].tipVelocity()[1]>300)cout<<fingers[i].id()<<":tap!"<<tap_ct++<<endl;
                        //cout<<fingers[i].tipVelocity()[1]<<endl;
                        
                        
                    }
                }
                
            }
        
        
        image.update_window("test Leap!");
        char key = cvWaitKey(10);
        if(key == 'q'){
            break;
        }
    }


}


int main() {
    // Create a sample listener and controller
    SampleListener listener;
    Controller controller;
    
    
    // Have the sample listener receive events from the controller
    controller.addListener(listener);
    
    //main loop
    cvmainloop();
    
    // Keep this process running until Enter is pressed
    /*
    std::cout << "Press Enter to quit..." << std::endl;
    std::cin.get();
    */
    // Remove the sample listener when done
    controller.removeListener(listener);
    
    return 0;
}
