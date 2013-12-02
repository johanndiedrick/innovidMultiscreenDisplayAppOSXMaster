#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //setup initial ip addresses
    iPadIP = "";
    iPhoneIP = "";
    osxIP = "";
    
    ofSetFrameRate(24);
    
    count = 0;
    
    debug = true;
    sendOSC = false;
    
    setupUI();
    setupVideo();
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    player.update();
    
    if(sendOSC){
    
	float p = player.getPosition();
	//printf("%f\n",p);
    
    ofxOscMessage m;
    m.setAddress( "/movie/position" );
    m.addFloatArg(p);
    
	// Broadcast current position information of movie
	if ((count % 20 == 0)) {

		osxSender.sendMessage(m); // send slower for macbook

	}
    
    iPadSender.sendMessage(m); //send every frame for iphone
    iPhoneSender.sendMessage(m); // send every frame for ipad
	count++;
    }

}

//--------------------------------------------------------------
void testApp::draw(){
    
    player.draw(0,0, 1280, 800);
    
    if(debug){
        drawDebug();
    }
}

//--------------------------------------------------------------
void testApp::setupOSC(){
    
    //set up osc and counter
    iPadSender.setup(iPadIP, PORT);
    iPhoneSender.setup(iPhoneIP, PORT);
    osxSender.setup(osxIP, PORT);
}

//--------------------------------------------------------------
void testApp::setupVideo(){
    
    //load movie and start playing
    player.loadMovie("movies/1124-macbook.mov");
    player.play();
}
//--------------------------------------------------------------

void testApp::drawDebug(){
    //draw some debug shit on screen
    
    ofDrawBitmapString("frame: " + ofToString(player.getCurrentFrame()) + "/"+ofToString(player.getTotalNumFrames()),50,50);
    ofDrawBitmapString("position: " + ofToString(player.getPosition()),50,70);
    ofDrawBitmapString("iPhone IP: " + iPhoneIP,50,90);
    ofDrawBitmapString("OSX Client IP: "+ osxIP, 50,110);
    ofDrawBitmapString("iPad IP: " + iPadIP ,50,130);

    
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    if(key=='f'){
        ofToggleFullscreen();
    }
    
    if(key=='d'){
        
        printf("drawing debug");
        debug = !debug;
    }

}
//--------------------------------------------------------------

void testApp::exit()
{
    gui->saveSettings("GUI/guiSettings.xml");
    delete gui;
}
//--------------------------------------------------------------

void testApp::setupUI()
{
	gui = new ofxUICanvas(50, 150, 320, 320);
    gui->addWidgetDown(new ofxUILabel("IP Addresses", OFX_UI_FONT_LARGE));
	gui->setWidgetFontSize(OFX_UI_FONT_LARGE);
	gui->addTextInput("iPhone IP", "iPhone IP Address", 10)->setAutoClear(false);
    gui->addTextInput("OS X IP", "Macbook Pro/Mac Mini IP Address", 10)->setAutoClear(false);
    gui->addTextInput("iPad IP", "iPad IP Address", 10)->setAutoClear(false);
	gui->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
    gui->addWidgetDown(new ofxUIToggle(32, 32, false, "SEND OSC"));
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent);
    gui->loadSettings("GUI/guiSettings.xml");
}
//--------------------------------------------------------------

void testApp::guiEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
	int kind = e.widget->getKind();
	cout << "got event from: " << name << endl;
	
	if(name == "iPhone IP")
    {
        ofxUITextInput *textinput = (ofxUITextInput *) e.widget;
        if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
        {
            iPhoneIP = textinput->getTextString();
            cout << "ON ENTER: ";
            //            ofUnregisterKeyEvents((testApp*)this);
        }
        else if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS)
        {
            cout << "ON FOCUS: ";
        }
        else if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS)
        {
            cout << "ON BLUR: ";
            //            ofRegisterKeyEvents(this);
        }
        string output = textinput->getTextString();
        cout << output << endl;
    }
    
    if(name == "OS X IP")
    {
        ofxUITextInput *textinput = (ofxUITextInput *) e.widget;
        if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
        {
            osxIP = textinput->getTextString();

            cout << "ON ENTER: ";
            //            ofUnregisterKeyEvents((testApp*)this);
        }
        else if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS)
        {
            cout << "ON FOCUS: ";
        }
        else if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS)
        {
            cout << "ON BLUR: ";
            //            ofRegisterKeyEvents(this);
        }
        string output = textinput->getTextString();
        cout << output << endl;
    }
    
    if(name == "iPad IP")
    {
        ofxUITextInput *textinput = (ofxUITextInput *) e.widget;
        if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_ENTER)
        {
            
            iPadIP = textinput->getTextString();

            cout << "ON ENTER: ";
            //            ofUnregisterKeyEvents((testApp*)this);
        }
        else if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_FOCUS)
        {
            cout << "ON FOCUS: ";
        }
        else if(textinput->getTriggerType() == OFX_UI_TEXTINPUT_ON_UNFOCUS)
        {
            cout << "ON BLUR: ";
            //            ofRegisterKeyEvents(this);
        }
        string output = textinput->getTextString();
        cout << output << endl;
    }
    
    else if(name == "SEND OSC")
    {
        cout << "sending osc" << endl;
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        setupOSC();
        sendOSC = toggle->getValue();
    }
    
    
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
