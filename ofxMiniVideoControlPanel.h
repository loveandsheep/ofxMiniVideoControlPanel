//
//  ofxMiniVideoControlPanel.h
//  sfpr_mapping_pattern
//
//  Created by Ovis aries on 12/09/10.
//
//

#include "ofMain.h"
#include "ofxOsc.h"

class ofxMiniVideoControlPanel{
public:
	ofxMiniVideoControlPanel();
	~ofxMiniVideoControlPanel();
	
	
	void mouseMoved(ofMouseEventArgs & args);
	void mousePressed(ofMouseEventArgs & args);
	void mouseDragged(ofMouseEventArgs & args);
	void mouseReleased(ofMouseEventArgs & args);
	
	void keyPressed(ofKeyEventArgs & key);
	void keyReleased(ofKeyEventArgs & key);
	
    void setVideo(string filename);
    void setPosition(float pct);
    void setPaused(bool paused);
	void drawPanel(int x,int y);
	ofPoint drawPoint;
	ofVideoPlayer video;
	
	bool onMouse[3];
    
    void enableOscReceive(int port);
    void enableOscSend(string address,int port);
    void disableOsc();
    
    bool isEnableOsc;
    bool isSender;
    
    ofxOscReceiver _receiver;
    ofxOscSender _sender;
};