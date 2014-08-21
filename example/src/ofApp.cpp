#include "ofApp.h"
#include <memory>
#include "nanoVG.hpp"


//using namespace ofx::nvg;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate( 60 );
    mNanoVG = std::shared_ptr<ofx::nvg::Context>( new ofx::nvg::Context( true, false ) );
    for( int i = 0; i < 100; i++ ) {
        mPoints.push_back( ofVec2f( ofRandom( 450 ), ofRandom( 450 ) ) );
        mControlPoints.push_back( ofVec2f( ofRandom( 450 ), ofRandom( 450 ) ) );
        cout << mPoints[ i ] << endl;
    }
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground( 0 );
    mNanoVG->beginFrame(450, 450, 1);
    mNanoVG->lineCap( 1 );
    mNanoVG->strokeColor( ofFloatColor( 1, 1, 1 , 1 ) );
    mNanoVG->strokeWidth( 5 );
    mNanoVG->beginPath();
    //mNanoVG->arc( 500, 500, r, -M_PI_2, fmodf(time, M_PI * 2.0f) - M_PI_2, NVG_CW );
    mNanoVG->moveTo(20, 20);
    int i =0;
    for( ofVec2f point : mPoints ) {
        mNanoVG->quadTo( point.x, point.y, mControlPoints[ i ].x, mControlPoints[ i ].y );
        
        i++;
    }
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