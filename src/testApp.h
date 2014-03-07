#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxUI.h"
#include "ofxJSONElement.h"
#define PORT 12345

class testApp : public ofBaseApp{

	public:
        //of setup, update draw
		void setup();
		void update();
		void draw();
    
        //video and osc
        ofVideoPlayer player;
        int count;
        void setupVideo();
        void downloadVideos();
        void changeVideo(string video);
    
        ofxOscSender iPadSender;
        ofxOscSender iPhoneSender;
        ofxOscSender osxSender;
        string iPadIP;
        string iPhoneIP;
        string osxIP;
        bool sendOSC;
        void setupOSC();
    
        //JSON
        ofxJSONElement response;
        std::stringstream ss;
        void getJSON();
        bool gotJSON;
        void updateJSONDebug();
        void loadJSON();
    
        //UI - key presses, drawing debug
        bool debug;
        void drawDebug();
        void keyPressed(int key);
    
        //ofxUI
        ofxUICanvas *gui;
        ofxUIDropDownList *ddl;
        void setupUI();
        void exit();
        void guiEvent(ofxUIEventArgs &e);
        void updateDDL();
    
        //system calls
        string ofSystemCall(string command);
    
};
