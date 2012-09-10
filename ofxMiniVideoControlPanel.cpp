//
//  ofxMiniVideoControlPanel.cpp
//  sfpr_mapping_pattern
//
//  Created by Ovis aries on 12/09/10.
//
//

#include "ofxMiniVideoControlPanel.h"

ofxMiniVideoControlPanel::ofxMiniVideoControlPanel(){
	ofRegisterMouseEvents(this);
	ofRegisterKeyEvents(this);
}

ofxMiniVideoControlPanel::~ofxMiniVideoControlPanel(){
	ofUnregisterMouseEvents(this);
	ofUnregisterKeyEvents(this);
}

void ofxMiniVideoControlPanel::drawPanel(int x, int y){
	video.update();
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
			if (i == 0) video.setPosition(0);
			if (i == 1){
				video.setPaused(!video.isPaused());
			}
		}
	}
	ofRectangle seek = ofRectangle(drawPoint.x,drawPoint.y,200,20);
	if (seek.inside(args.x,args.y)){
		video.setPosition((args.x - drawPoint.x)/200.0);
	}
}

void ofxMiniVideoControlPanel::mouseDragged(ofMouseEventArgs &args){
	for (int i = 0;i < 3;i++){
		ofRectangle checker = ofRectangle(drawPoint.x+i*20,drawPoint.y+20,20,20);
		
		if (checker.inside(args.x,args.y)){
			if (i == 0) video.setPosition(0);
			if (i == 1){
				video.setPaused(!video.isPaused());
			}
		}
	}
	ofRectangle seek = ofRectangle(drawPoint.x,drawPoint.y,200,20);
	if (seek.inside(args.x,args.y)){
		video.setPosition((args.x - drawPoint.x)/200.0);
	}
}

void ofxMiniVideoControlPanel::mouseReleased(ofMouseEventArgs &args){
	
}

void ofxMiniVideoControlPanel::keyPressed(ofKeyEventArgs &key){
	
}

void ofxMiniVideoControlPanel::keyReleased(ofKeyEventArgs &key){
	
}