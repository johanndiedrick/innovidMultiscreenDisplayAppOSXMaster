#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "169.254.113.109"
#define HOST2 "169.254.77.75"
#define HOST3 "169.254.147.227"
#define PORT 12345

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

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
        int count;
    
        //osc sender
        ofxOscSender sender;
        ofxOscSender sender2;
        ofxOscSender sender3;
    
		
};
