#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

    //load movie and start playing
    player.loadMovie("movies/macbook4s-demo.mov");
    player.play();
    
    //set up osc and counter
    sender.setup(HOST, PORT);
    count = 0;

}

//--------------------------------------------------------------
void testApp::update(){
    
    player.update();
    
    player.update();
	float p = player.getPosition();
	printf("%f\n",p);
    
	// Broadcast current position information of movie
	//if ((count % 20 == 0)) {
		ofxOscMessage m;
		m.setAddress( "/movie/position" );
		m.addFloatArg(p);
		sender.sendMessage(m);
	//}
	count++;

}

//--------------------------------------------------------------
void testApp::draw(){

    player.draw(0,0, 1280, 800);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
