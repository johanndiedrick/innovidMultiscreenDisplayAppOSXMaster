#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxUI.h"

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
        void setupOSC();
        void setupVideo();
        void drawDebug();
        void setupUI();
    
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    
        //video player
        ofVideoPlayer player;
        bool switchVideo;
        int count;
    
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
    
        //draw debug
        bool debug;

    
		
};
