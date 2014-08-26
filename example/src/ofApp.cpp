#include "ofApp.h"
#include <memory>
#include "nanoVG.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate( 60 );
    ofSetBackgroundAuto( false );
    ofBackground(0);
    mNanoVG = std::shared_ptr<ofx::nvg::Context>( new ofx::nvg::Context( true, false ) );
    mCanvasSize = ofVec2f( 900, 900 );
    
    mFbo.allocate( mCanvasSize.x, mCanvasSize.y );
    mFbo.bind();
    ofClear(0, 0, 0);
    mFbo.unbind();
    
    mTempFbo.allocate( mCanvasSize.x, mCanvasSize.y );
    mTempFbo.bind();
    ofClear(0, 0, 0);
    mTempFbo.unbind();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(100);
    ofSetColor( 0, 255, 255 );
    for( ofVec2f point : mLine.getVertices() ) {
        ofCircle( point.x, point.y, 6 );
    }
    ofSetColor( 255, 255, 255 );
    
    mFbo.draw( 0, mCanvasSize.y, mCanvasSize.x, - mCanvasSize.y );
    mTempFbo.draw( 0, mCanvasSize.y, mCanvasSize.x, - mCanvasSize.y );
    
    glViewport( 0, 0, mCanvasSize.x, mCanvasSize.y );
    
    ofSetColor( 0, 0, 255 );
    mLine.draw();
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
    mLine.addVertex( x, y );
    mPositionCount++;
    mBezier[ mPositionCount ] = ofVec2f( x, y );
    
    if ( mPositionCount != 4 )
    {
        cout << "mPositionCount: " << mPositionCount << endl;
        mFbo.bind();
        mNanoVG->beginFrame( mCanvasSize.x, mCanvasSize.y, 1 );
        mNanoVG->beginPath();
        
        mNanoVG->circle( x, y, 2 );
        
        mNanoVG->strokeColor( ofFloatColor( 1, 0, 0, 1 ) );
        mNanoVG->strokeWidth( 4 );
        mNanoVG->stroke();
        mNanoVG->endFrame();
        
        mFbo.unbind();
        
        mTempFbo.bind();
        mNanoVG->beginFrame( mCanvasSize.x, mCanvasSize.y, 1 );
        mNanoVG->beginPath();
        
        mNanoVG->moveTo( mBezier[ 0 ] );
        for( int i = 1; i < mPositionCount + 1; i++ ) {
            mNanoVG->lineTo( mBezier[ i ] );
        }
        mNanoVG->lineCap( 1 );
        mNanoVG->strokeColor( ofFloatColor( 0, 1, 0 ,1 ) );
        mNanoVG->strokeWidth( 5 );
        mNanoVG->stroke();
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
        
        mNanoVG->lineCap( 1 );
        mNanoVG->strokeColor( ofFloatColor( 1, 1, 1 ,1 ) );
        mNanoVG->strokeWidth( 5 );
        mNanoVG->stroke();
        
        mNanoVG->beginPath();
        mNanoVG->circle( x, y, 2 );
        
        mNanoVG->strokeColor( ofFloatColor( 1, 0, 0, 1 ) );
        mNanoVG->strokeWidth( 4 );
        mNanoVG->stroke();
        
        mNanoVG->endFrame();
        mFbo.unbind();
        
        //[self setNeedsDisplay];
        // replace points and get ready to handle the next segment
        mBezier[ 0 ] = mBezier[ 3 ];
        mBezier[ 1 ] = mBezier[ 4 ];
        mPositionCount = 1;
        
        mTempFbo.bind();
        cout << "CLEAR!     " << "mPositionCount: " << mPositionCount << endl;
        ofClear(0, 0, 0);
        
        mNanoVG->beginFrame( mCanvasSize.x, mCanvasSize.y, 1 );
        mNanoVG->beginPath();
        
        mNanoVG->moveTo( mBezier[ 0 ] );
        mNanoVG->lineTo( mBezier[ 1 ] );
        mNanoVG->lineCap( 1 );
        mNanoVG->strokeColor( ofFloatColor( 1, 1, 0 , 1 ) );
        mNanoVG->strokeWidth( 5 );
        mNanoVG->stroke();
        mNanoVG->endFrame();
        
        mTempFbo.unbind();
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    mPositionCount = 0;
    mBezier[ 0 ] = ofVec2f( x, y );
    
    mLine.addVertex( x, y );
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    mPositionCount = 0;
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