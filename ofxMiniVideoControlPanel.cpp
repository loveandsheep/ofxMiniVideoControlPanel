//
//  ofxMiniVideoControlPanel.cpp
//  sfpr_mapping_pattern
//
//  Created by Ovis aries on 12/09/10.
//
//

#include "ofxMiniVideoControlPanel.h"

ofxMiniVideoControlPanel::ofxMiniVideoControlPanel(){
    ofAddListener(ofEvents().mouseMoved, this, &ofxMiniVideoControlPanel::mouseMoved);
    ofAddListener(ofEvents().mousePressed, this, &ofxMiniVideoControlPanel::mousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &ofxMiniVideoControlPanel::mouseReleased);
    ofAddListener(ofEvents().mouseDragged, this, &ofxMiniVideoControlPanel::mouseDragged);
    
    ofAddListener(ofEvents().keyPressed, this, &ofxMiniVideoControlPanel::keyPressed);
    ofAddListener(ofEvents().keyReleased, this, &ofxMiniVideoControlPanel::keyReleased);
}

ofxMiniVideoControlPanel::~ofxMiniVideoControlPanel(){
    ofRemoveListener(ofEvents().mouseMoved, this, &ofxMiniVideoControlPanel::mouseMoved);
    ofRemoveListener(ofEvents().mousePressed, this, &ofxMiniVideoControlPanel::mousePressed);
    ofRemoveListener(ofEvents().mouseReleased, this, &ofxMiniVideoControlPanel::mouseReleased);
    ofRemoveListener(ofEvents().mouseDragged, this, &ofxMiniVideoControlPanel::mouseDragged);
    
    ofRemoveListener(ofEvents().keyPressed, this, &ofxMiniVideoControlPanel::keyPressed);
    ofRemoveListener(ofEvents().keyReleased, this, &ofxMiniVideoControlPanel::keyReleased);
}

void ofxMiniVideoControlPanel::drawPanel(int x, int y){
	video.update();
    
    if (!isSender){
        while (_receiver.hasWaitingMessages()){
            ofxOscMessage m;
            _receiver.getNextMessage(&m);
            if (m.getAddress() == "/MVC/Play"){
                video.setPaused(false);
            }
            if (m.getAddress() == "/MVC/Pause"){
                video.setPaused(true);
            }
            if (m.getAddress() == "/MVC/SetPos"){
                video.setPosition(m.getArgAsFloat(0));
            }
            if (m.getAddress() == "/MVC/SetVideo"){
                setVideo(m.getArgAsString(0));
            }
        }
    }
    
	drawPoint = ofPoint(x,y);
	ofPushMatrix();
	ofTranslate(x, y);
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	
	ofSetColor(0);
	ofRect(0,0,200,40);
	ofSetColor(255);
	ofDrawBitmapString("<<", 2,34);
	
	if (!video.isPaused()) ofDrawBitmapString("||", 22,34);
	else ofDrawBitmapString("|>", 22,34);
	
	ofDrawBitmapString(">>",42,34);
	ofNoFill();
	ofRect( 0, 0, 200, 40);
	ofFill();
	for (int i = 0;i < 3;i++){
		ofNoFill();
		ofSetColor(255);
		ofRect(i*20,20,20,20);
		ofFill();
		if (onMouse[i]){
			ofEnableBlendMode(OF_BLENDMODE_ADD);
			ofSetColor(255,20, 200,128);
			ofRect(i*20,20,20,20);
			ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		}
	}
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofSetColor(255,20, 200,128);
	ofRect(0,0,video.getPosition()*200.0,20.0);
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetColor(255);
	ofLine(video.getPosition()*200.0, 0, video.getPosition()*200, 20);
	string time_s,time_m;
	time_s = ofToString((int)(video.getDuration()*video.getPosition())%60);
	time_m = ofToString((int)(video.getDuration()*video.getPosition())/60);
	ofDrawBitmapString(time_m+":"+time_s, 0,60);
//	ofDrawBitmapString(video.getCurrentFrame(), 0,80);
	
	ofPopMatrix();
}

void ofxMiniVideoControlPanel::mouseMoved(ofMouseEventArgs &args){

	for (int i = 0;i < 3;i++){
		ofRectangle checker = ofRectangle(drawPoint.x+i*20,drawPoint.y+20,20,20);
		onMouse[i] = checker.inside(args.x,args.y);
	}
	
}

void ofxMiniVideoControlPanel::mousePressed(ofMouseEventArgs &args){
	for (int i = 0;i < 3;i++){
		ofRectangle checker = ofRectangle(drawPoint.x+i*20,drawPoint.y+20,20,20);
		
		if (checker.inside(args.x,args.y)){
			if (i == 0) {
                setPosition(0);
            }
			if (i == 1){
				setPaused(!video.isPaused());
			}
		}
	}
	ofRectangle seek = ofRectangle(drawPoint.x,drawPoint.y,200,20);
	if (seek.inside(args.x,args.y)){
		setPosition((args.x - drawPoint.x)/200.0);
	}
}

void ofxMiniVideoControlPanel::mouseDragged(ofMouseEventArgs &args){
	for (int i = 0;i < 3;i++){
		ofRectangle checker = ofRectangle(drawPoint.x+i*20,drawPoint.y+20,20,20);
		
		if (checker.inside(args.x,args.y)){
			if (i == 0) setPosition(0);
			if (i == 1){
				setPaused(!video.isPaused());
			}
		}
	}
	ofRectangle seek = ofRectangle(drawPoint.x,drawPoint.y,200,20);
	if (seek.inside(args.x,args.y)){
		setPosition((args.x - drawPoint.x)/200.0);
	}
}

void ofxMiniVideoControlPanel::mouseReleased(ofMouseEventArgs &args){
	
}

void ofxMiniVideoControlPanel::keyPressed(ofKeyEventArgs &key){
	
}

void ofxMiniVideoControlPanel::keyReleased(ofKeyEventArgs &key){
	
}

void ofxMiniVideoControlPanel::enableOscReceive(int port){
    isEnableOsc = true;
    isSender = false;
    
    _receiver.setup(port);
}

void ofxMiniVideoControlPanel::enableOscSend(string address, int port){
    isEnableOsc = true;
    isSender = true;
    
    _sender.setup(address, port);
}

void ofxMiniVideoControlPanel::setVideo(string filename){
    video.loadMovie(filename);
    if (isSender){
        ofxOscMessage m;
        m.setAddress("/MVC/SetVideo");
        m.addStringArg(filename);
        _sender.sendMessage(m);
    }
    video.play();
    video.setPaused(true);
    video.setPosition(0);
}

void ofxMiniVideoControlPanel::setPaused(bool paused){
    if (isSender){
        ofxOscMessage m;
        if (!paused) m.setAddress("/MVC/Play");
        if ( paused) m.setAddress("/MVC/Pause");
        _sender.sendMessage(m);
    }
    video.setPaused(paused);
    setPosition(video.getPosition());
}

void ofxMiniVideoControlPanel::setPosition(float pct){
    if (isSender){
        ofxOscMessage m;
        m.setAddress("/MVC/SetPos");
        m.addFloatArg(pct);
        _sender.sendMessage(m);
    }
    video.setPosition(pct);
}