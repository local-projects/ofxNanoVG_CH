#include "ofApp.h"
#include <memory>
#include "nanoVG.hpp"


//using namespace ofx::nvg;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate( 60 );
    mNanoVG = std::shared_ptr<ofx::nvg::Context>( new ofx::nvg::Context( true, true ) );
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    float time = ofGetElapsedTimef();
    float r = 200.0f;
    
    mNanoVG->beginFrame(1024, 768, 1);
    mNanoVG->beginPath();
    mNanoVG->arc( 500, 500, r, -M_PI_2, fmodf(time, M_PI * 2.0f) - M_PI_2, NVG_CW );
    mNanoVG->strokeColor( ofFloatColor( .3, .3, .3 , 1 ) );
    mNanoVG->strokeWidth( 5 );
    mNanoVG->stroke();
    mNanoVG->endFrame();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}