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
    ofClear(0);
    ofSetColor( 255, 0, 0 );
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, fb->texture );
    
    glBegin( GL_QUADS );
    
    glTexCoord2f( 0, 1 ); glVertex3i( 0, 0, 0 );
    glTexCoord2f( 0, 0 ); glVertex3i( 0, 450, 0 );
    glTexCoord2f( 1, 0 ); glVertex3i( 450, 450, 0 );
    glTexCoord2f( 1, 1 ); glVertex3i( 450, 0, 0 );
    
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
        
        nvgluBindFramebuffer(fb);
        mNanoVG->beginFrame(450, 450, 1);
        mNanoVG->beginPath();
        
        /*cout << drawnBezierPathsCounter << " < " << bezierPathCounter << " total " << bezierPoints.size()  << "  " << (drawnBezierPathsCounter * 4 + 3) << endl;*/
        mNanoVG->moveTo(    pts[0] );
        mNanoVG->bezierTo(  pts[1],
                            pts[2],
                            pts[3]);
        
        mNanoVG->lineCap( 1 );
        mNanoVG->strokeColor( ofFloatColor( 1, 1, 1 ,1 ) );
        mNanoVG->strokeWidth( 5 );
        mNanoVG->stroke();
        mNanoVG->endFrame();
        nvgluBindFramebuffer(NULL);
        
        //[self setNeedsDisplay];
        // replace points and get ready to handle the next segment
        pts[0] = pts[3];
        pts[1] = pts[4];
        ctr = 1;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ctr = 0;
    pts[0] = ofVec2f( x, y );
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