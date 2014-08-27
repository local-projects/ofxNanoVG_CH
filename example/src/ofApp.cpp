#include "ofApp.h"
#include <memory>
#include "nanoVG.hpp"

#define DEBUG 0

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate( 60 );
    ofSetBackgroundAuto( false );
    ofBackground(0);
    mNanoVG = std::shared_ptr<ofx::nvg::Context>( new ofx::nvg::Context( true, false ) );
    mCanvasSize = ofVec2f( 900, 900 );
    
    red = ofFloatColor( 1, 0, 0, 1 );
    green = ofFloatColor( 0, 1, 0, 1 );
    white = ofFloatColor( 1, 1, 1, 1 );
    cyan = ofFloatColor( 0, 1, 1, 1 );
    blue = ofFloatColor( 0, 0, 1, 1 );
    
    mFbo.allocate( mCanvasSize.x, mCanvasSize.y );
    mFbo.bind();
    clear();
    mFbo.unbind();
    
    mTempFbo.allocate( mCanvasSize.x, mCanvasSize.y );
    mTempFbo.bind();
    clear();
    mTempFbo.unbind();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(100);
    ofSetColor( cyan );
    for( ofVec2f point : mLine.getVertices() ) {
        ofCircle( point.x, point.y, 6 );
    }
    ofSetColor( white );
    
    mFbo.draw( 0, mCanvasSize.y, mCanvasSize.x, - mCanvasSize.y );
    mTempFbo.draw( 0, mCanvasSize.y, mCanvasSize.x, - mCanvasSize.y );
    
    if( DEBUG ) {
        ofSetColor( blue );
        mLine.draw();
    }
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
    if( DEBUG ) {
        mLine.addVertex( x, y );
    }
    mPositionCount++;
    mBezier[ mPositionCount ] = ofVec2f( x, y );
    
    if ( mPositionCount != 4 )
    {
        if( DEBUG ) {
            cout << "mPositionCount: " << mPositionCount << endl;
            mFbo.bind();
            mNanoVG->beginFrame( mCanvasSize.x, mCanvasSize.y, 1 );
            mNanoVG->beginPath();
            
            mNanoVG->circle( x, y, 2 );
            stroke(1, red, 4);
            mNanoVG->endFrame();
            
            mFbo.unbind();
        }
        
        mTempFbo.bind();
        clear();
        ofSetColor( white );
        mNanoVG->beginFrame( mCanvasSize.x, mCanvasSize.y, 1 );
        mNanoVG->beginPath();
        
        mNanoVG->moveTo( mBezier[ 0 ] );
        for( int i = 1; i < mPositionCount + 1; i++ ) {
            mNanoVG->lineTo( mBezier[ i ] );
        }
        if( DEBUG ) {
            stroke( 1, green, 5 );
        } else {
            stroke( 1, white, 5 );
        }
        mNanoVG->endFrame();
        mTempFbo.unbind();
    } else {
        
        mBezier[ 3 ] = ofVec2f( ( mBezier[ 2 ].x + mBezier[ 4 ].x ) / 2.0,
                               ( mBezier[ 2 ].y + mBezier[ 4 ].y) / 2.0 );
        // move the endpoint to the middle of the line joining the second control point
        // of the first Bezier segment and the first control point of the second Bezier segment
        
        mFbo.bind();
        mNanoVG->beginFrame( mCanvasSize.x, mCanvasSize.y, 1 );
        mNanoVG->beginPath();
        
        mNanoVG->moveTo(    mBezier[ 0 ] );
        mNanoVG->bezierTo(  mBezier[ 1 ],
                            mBezier[ 2 ],
                            mBezier[ 3 ]);
        
        stroke(1, white, 5);
        
        if( DEBUG ) {
            mNanoVG->beginPath();
            mNanoVG->circle( x, y, 2 );
            stroke( 1, red, 4 );
        }
        
        mNanoVG->endFrame();
        mFbo.unbind();
        
        // replace points and get ready to handle the next segment
        mBezier[ 0 ] = mBezier[ 3 ];
        mBezier[ 1 ] = mBezier[ 4 ];
        mPositionCount = 1;
        
        mTempFbo.bind();
        clear();
        ofSetColor( white );
        if( DEBUG ) {
            cout << "CLEAR!     " << "mPositionCount: " << mPositionCount << endl;
        }
        
        mNanoVG->beginFrame( mCanvasSize.x, mCanvasSize.y, 1 );
        mNanoVG->beginPath();
        
        mNanoVG->moveTo( mBezier[ 0 ] );
        mNanoVG->lineTo( mBezier[ 1 ] );
        stroke(1, white, 5);
        mNanoVG->endFrame();
        
        mTempFbo.unbind();
    }
}

void ofApp::stroke( int cap, ofFloatColor color, int width )
{
    mNanoVG->lineCap( cap );
    mNanoVG->strokeColor( color );
    mNanoVG->strokeWidth( width );
    mNanoVG->stroke();
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mPositionCount = 0;
    mBezier[ 0 ] = ofVec2f( x, y );
    
    if( DEBUG ) {
        mLine.clear();
        mLine.addVertex( x, y );
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    mPositionCount = 0;
    mFbo.bind();
    ofSetColor( white );
    mTempFbo.draw( 0, mCanvasSize.y, mCanvasSize.x, - mCanvasSize.y );
    mFbo.unbind();
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