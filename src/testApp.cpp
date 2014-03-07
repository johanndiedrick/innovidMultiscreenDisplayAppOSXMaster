#include "testApp.h"

#pragma mark - OF Setup, Update, Draw

//--------------------------------------------------------------
void testApp::setup(){
    switchVideo = false;
    
    //setup initial ip addresses
    iPadIP = "";
    iPhoneIP = "";
    osxIP = "";
    
    ofSetFrameRate(24);
    
    count = 0;
    
    debug = false;
    sendOSC = false;
    
    setupUI();
    setupVideo();
    
    CGDisplayHideCursor(NULL);
    
    gotJSON = false;
    
    //load json
    loadJSON();
    
    ss << "No video information received yet" << endl;
    
    
    
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
    m.addIntArg(debug);
    
	// Broadcast current position information of movie
	if ((count % 100 == 0)) {

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

# pragma mark - Video and OSC

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
    player.loadMovie("movies/macbook.mov");
    player.play();
}


//--------------------------------------------------------------
void testApp::downloadVideos(){
    cout << "downloading videos" << endl;
    for (int i=0; i<response["videos"].size(); i++){
        string video_url = response["videos"][i]["link"].asString();
        string video_filename = "movies/" + response["videos"][i]["filename"].asString();
        string video_final_path = ofToDataPath(video_filename, true);
        cout << video_url << endl;
        string command = "curl -o "+video_final_path+ " " + video_url;
        ofSystemCall(command);
    }
}

void testApp::changeVideo(string video){
    string video_path = "movies/" + video;
    player.stop();
    player.loadMovie(video_path);
    player.play();
}

#pragma mark - JSON


//--------------------------------------------------------------
void testApp::loadJSON(){

    //if json isn't there
    ofFile json;
    string json_file_path = "json/innovid_videos.json";
    if ( !json.doesFileExist(ofToDataPath(json_file_path, true)) ) {

        //download, save and load json
        //this is done on the ui now by hitting the update json button.
        //could do automatically, but maybe not good if you're not online

        cout << "json file doesn't exist, lets try to download it" << endl;
        
    }else if( json.doesFileExist(ofToDataPath(json_file_path, true)) ){
        
        //else, load saved json
        
        cout << "json file exists, lets load it!!!" << endl;
        std::string file = "json/innovid_videos.json";
        
        // Now parse the JSON
        bool parsingSuccessful = response.open(file);
        
        if (parsingSuccessful) {
            updateJSONDebug();
            updateDDL();
            /*
            // now write pretty print
            if(!result.save("example_output_pretty.json",true)) {
                cout << "example_output_pretty.json written unsuccessfully." << endl;
            } else {
                cout << "example_output_pretty.json written successfully." << endl;
            }
            
            // now write without pretty print
            if(!result.save("example_output_fast.json",false)) {
                cout << "example_output_pretty.json written unsuccessfully." << endl;
            } else {
                cout << "example_output_pretty.json written successfully." << endl;
            }
            */
        } else {
            cout  << "Failed to parse JSON" << endl;
        }
    }
    

}

//--------------------------------------------------------------

void testApp::getJSON(){
    cout << "Getting JSON..." << endl;
    ss.str(std::string()); // clear string stream
    ss << "Getting JSON..." << endl;
    
    //get json
    std::string url = "http://stormy-badlands-2316.herokuapp.com/data";
    
    if (!response.open(url)) {
		cout  << "Failed to parse JSON\n" << endl;
        ss.str(std::string()); // clear string stream
        ss << "Failed to parse JSON\n" << endl;
	}else{
        gotJSON = true;
        ss.str(std::string()); // clear string stream
        
        //save json file
        std::string json_final_path =ofToDataPath("json/innovid_videos.json", true);
        string command = "mkdir "+ofToDataPath("json", true);
        ofSystemCall(command);
        command = "curl -o "+json_final_path+ " " + url;
        ofSystemCall(command);
        
        updateJSONDebug();
        updateDDL();
        
    }

}

void testApp::updateJSONDebug(){
    //update string stream w json data
    ss<< "number of videos in backend: " << response["videos"].size() << "\n" << endl;
    for (int i=0; i<response["videos"].size(); i++){
        ss << "video " << i+ 1 // +1 for pretty, "non-coder" numbers
        << "\n"
        << "title: "
        << response["videos"][i]["title"].asString()
        << "\n"
        << "filename: "
        << response["videos"][i]["filename"].asString()
        << "\n"
        << "timestamp: "
        <<  response["videos"][i]["timestamp"].asString()
        << "\n"
        << endl;
    }
}

#pragma mark - UI - Key Presses, drawing debug

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key=='f'){
        ofToggleFullscreen();
    }
    
    if(key=='d'){
        debug = !debug;
        gui->toggleVisible();
    }
}

//--------------------------------------------------------------

void testApp::drawDebug(){
    //show cursor
    CGDisplayShowCursor(NULL);
    
    //draw some debug shit on screen
    
    ofDrawBitmapString("frame: " + ofToString(player.getCurrentFrame()) + "/"+ofToString(player.getTotalNumFrames()),50,50);
    ofDrawBitmapString("position: " + ofToString(player.getPosition()),50,70);
    ofDrawBitmapString("iPhone IP: " + iPhoneIP,50,90);
    ofDrawBitmapString("OSX Client IP: "+ osxIP, 50,110);
    ofDrawBitmapString("iPad IP: " + iPadIP ,50,130);
    ofDrawBitmapString("Currently playing: " + player.getMoviePath() ,50,150);
    ofDrawBitmapString("Sending OSC?: " + ofToString(sendOSC) ,50,170);
    ofDrawBitmapString(ss.str(), ofGetWidth()/2, 50); // draw json on right side of screen
}

#pragma mark - ofxUI

//--------------------------------------------------------------

void testApp::exit()
{
    gui->saveSettings("GUI/guiSettings.xml");
    delete gui;
}
//--------------------------------------------------------------

void testApp::setupUI()
{
	gui = new ofxUICanvas(50, 190, 320, 320);
    gui->addWidgetDown(new ofxUILabel("IP Addresses", OFX_UI_FONT_LARGE));
	gui->setWidgetFontSize(OFX_UI_FONT_LARGE);
	gui->addTextInput("iPhone IP", "iPhone IP Address", 10)->setAutoClear(false);
    gui->addTextInput("OS X IP", "Macbook Pro/Mac Mini IP Address", 10)->setAutoClear(false);
    gui->addTextInput("iPad IP", "iPad IP Address", 10)->setAutoClear(false);
	gui->setWidgetFontSize(OFX_UI_FONT_MEDIUM);
    gui->addWidgetDown(new ofxUIToggle(32, 32, false, "Sync Video"));
    gui->addButton("Download videos", false, 44, 44);
    gui->addButton("Update JSON", false, 44, 44);
    vector<string> names;
    names.push_back("Default Video");
    ddl = gui->addDropDownList("SELECT A VIDEO", names);
    ddl->setAutoClose(true);
    ofAddListener(gui->newGUIEvent, this, &testApp::guiEvent);
    gui->toggleVisible();
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
    
    else if(name == "Sync Video")
    {
        ofxUIToggle *toggle = (ofxUIToggle *) e.widget;
        setupOSC();
        sendOSC = toggle->getValue();
    }
    
    else if(name == "Download videos")
    {
        ofxUIButton *button = (ofxUIButton *) e.widget;
        //setupOSC();
        //sendOSC = toggle->getValue();
        if(button->getValue() == 1){
            downloadVideos();
        }
        //cout << name << "\t value: " << button->getValue() << endl;
    }
    
    else if(name == "Update JSON")
    {
        ofxUIButton *button = (ofxUIButton *) e.widget;
        //setupOSC();
        //sendOSC = toggle->getValue();
        if(button->getValue() == 1){
            getJSON();
        }
        //cout << name << "\t value: " << button->getValue() << endl;
    }
    
    else if(name == "SELECT A VIDEO")
    {
        ofxUIDropDownList *ddlist = (ofxUIDropDownList *) e.widget;
        vector<ofxUIWidget *> &selected = ddlist->getSelected();
        for(int i = 0; i < selected.size(); i++)
        {
            cout << "SELECTED: " << selected[i]->getName() << endl;
            changeVideo(selected[i]->getName());
        }
    }
}

void testApp::updateDDL(){
    //update our dropdown box with the videos
    for (int i=0; i<response["videos"].size(); i++){
        ddl->addToggle(response["videos"][i]["filename"].asString());
    }
}


#pragma mark - System calls

string testApp::ofSystemCall(string command)
{
    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) return "ERROR";
    char buffer[128];
    string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    result.erase(remove(result.begin(), result.end(), '\n'), result.end());
    return result;
}