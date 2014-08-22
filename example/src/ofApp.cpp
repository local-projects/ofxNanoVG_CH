#include "ofApp.h"
#include <memory>
#include "nanoVG.hpp"
#include "nanovg_gl_utils.h"

//using namespace ofx::nvg;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate( 60 );
    ofSetBackgroundAuto( false );
    ofBackground(0);
    mNanoVG = std::shared_ptr<ofx::nvg::Context>( new ofx::nvg::Context( true, false ) );
    /*for( int i = 0; i < 10; i++ ) {
        mPoints.push_back( ofVec2f( ofRandom( 450 ), ofRandom( 450 ) ) );
        mControlPoints.push_back( ofVec2f( ofRandom( 450 ), ofRandom( 450 ) ) );
    }*/
    
    //bezierPoints.reserve( 1000 );
    bezierPathCounter = 0;
    drawnBezierPathsCounter = 0;
    
    mNanoVG->resetScissor();
    
    fb = NULL;
    fb = nvgluCreateFramebuffer(mNanoVG->get(), 450, 450);
	if (fb == NULL) {
		printf("Could not create FBO.\n");
		return -1;
	}
    
    nvgluBindFramebuffer(fb);
    glViewport(0, 0, 450, 450);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    nvgluBindFramebuffer(NULL);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    nvgluBindFramebuffer(fb);
    mNanoVG->beginFrame(450, 450, 1);
    mNanoVG->beginPath();
    
    while ( drawnBezierPathsCounter < bezierPathCounter ) {
        cout << drawnBezierPathsCounter << " < " << bezierPathCounter << " total " << bezierPoints.size()  << "  " << (drawnBezierPathsCounter * 4 + 3) << endl;
        uint startIndex = drawnBezierPathsCounter * 4;
        mNanoVG->moveTo( bezierPoints[ startIndex + 0 ] );
        mNanoVG->bezierTo(  bezierPoints[ startIndex + 1 ],
                            bezierPoints[ startIndex + 2 ],
                            bezierPoints[ startIndex + 3 ]);
        drawnBezierPathsCounter++;
    }
    
    mNanoVG->lineCap( 1 );
    mNanoVG->strokeColor( ofFloatColor( 1, 1, 1 ,1 ) );
    mNanoVG->strokeWidth( 5 );
    mNanoVG->stroke();
    mNanoVG->endFrame();
    nvgluBindFramebuffer(NULL);
    
    
    ofClear(0);
    ofSetColor( 255, 0, 0 );
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, fb->texture );
    
    glBegin( GL_QUADS );
    
    glTexCoord2f( 0.f, 0.f ); glVertex3i( 0, 0, 0 );
    glTexCoord2f( 0.f, 1.f ); glVertex3i( 0, 450, 0 );
    glTexCoord2f( 1.0f, 1.0f ); glVertex3i( 450, 450, 0 );
    glTexCoord2f( 1, 0.f ); glVertex3i( 450, 0, 0 );
    
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, 0 );
    glDisable( GL_TEXTURE_2D );
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
    ctr++;
    pts[ctr] = ofVec2f( x, y );
    
    if (ctr == 4)
    {
        //cout << "draw" << endl;
        pts[3] = ofVec2f((pts[2].x + pts[4].x)/2.0, (pts[2].y + pts[4].y)/2.0);
        // move the endpoint to the middle of the line joining the second control point
        // of the first Bezier segment and the first control point of the second Bezier segment
        
        bezierPoints.push_back( pts[0] );
        bezierPoints.push_back( pts[1] );
        bezierPoints.push_back( pts[2] );
        bezierPoints.push_back( pts[3] );
        
        //[self setNeedsDisplay];
        // replace points and get ready to handle the next segment
        pts[0] = pts[3];
        pts[1] = pts[4];
        ctr = 1;
        
        bezierPathCounter++;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ctr = 0;
    pts[0] = ofVec2f( x, y );
    /*mPoints.clear();
    mControlPoints.clear();
    for( int i = 0; i < 10; i++ ) {
        mPoints.push_back( ofVec2f( ofRandom( 450 ), ofRandom( 450 ) ) );
        mControlPoints.push_back( ofVec2f( ofRandom( 450 ), ofRandom( 450 ) ) );
        cout << mPoints[ i ] << endl;
    }*/
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    ctr = 0;
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