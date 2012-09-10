//
//  ofxMiniVideoControlPanel.h
//  sfpr_mapping_pattern
//
//  Created by Ovis aries on 12/09/10.
//
//

#include "ofMain.h"

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
	
	void drawPanel(int x,int y);
	ofPoint drawPoint;
	ofVideoPlayer video;
	
	bool onMouse[3];
};