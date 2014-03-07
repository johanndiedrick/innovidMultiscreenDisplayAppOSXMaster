#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxUI.h"
#include "ofxJSONElement.h"



/*
#define HOST "169.254.113.109"
#define HOST2 "169.254.77.75"
#define HOST3 "169.254.147.227"
 */
#define PORT 12345

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
    
        //video sync
        void setupOSC();
        void setupVideo();
        void drawDebug();
        void setupUI();
        void keyPressed(int key);
    
        //get json
        void getJSON();
        bool gotJSON;
        std::stringstream ss;
    
        //downloading videos
        void downloadVideos();
    

        //json for videos
        ofxJSONElement  response;
        void loadJSON();

    
        //video player
        ofVideoPlayer player;
        bool switchVideo;
        int count;
        void changeVideo(string video);
    
        //osc sender
        ofxOscSender iPadSender;
        ofxOscSender iPhoneSender;
        ofxOscSender osxSender;
    
        string iPadIP;
        string iPhoneIP;
        string osxIP;
    
        bool sendOSC;
    
        //ofx ui
        ofxUICanvas *gui;
        void exit();
        void guiEvent(ofxUIEventArgs &e);
        ofxUIDropDownList *ddl;

    
        //draw debug
        bool debug;

    
		
};
