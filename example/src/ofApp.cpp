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
    
    mCanvasSize = ofVec2f( 900, 900 );
    
    fb = NULL;
    fb = nvgluCreateFramebuffer( mNanoVG->get(), mCanvasSize.x,  mCanvasSize.y );
	if (fb == NULL) {
		printf("Could not create FBO.\n");
		return -1;
	}
    
    nvgluBindFramebuffer( fb );
    glViewport( 0, 0, mCanvasSize.x, mCanvasSize.y );
	glClearColor( 0, 0, 0, 0 );
	glClear( GL_COLOR_BUFFER_BIT|GL_STENCIL_BUFFER_BIT );
    nvgluBindFramebuffer( NULL );
    
    mLine = ofPolyline();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofClear(100);
    ofSetColor( 255, 255, 255 );
    glEnable( GL_TEXTURE_2D );
    glBindTexture( GL_TEXTURE_2D, fb->texture );
    
    glBegin( GL_QUADS );
    
    glTexCoord2f( 0, 1 ); glVertex3i( 0, 0, 0 );
    glTexCoord2f( 0, 0 ); glVertex3i( 0, mCanvasSize.y, 0 );
    glTexCoord2f( 1, 0 ); glVertex3i( mCanvasSize.x, mCanvasSize.y, 0 );
    glTexCoord2f( 1, 1 ); glVertex3i( mCanvasSize.x, 0, 0 );
    
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, 0 );
    glDisable( GL_TEXTURE_2D );
    
    glViewport( 0, 0, mCanvasSize.x, mCanvasSize.y );
    
    ofSetColor( 0, 0, 255 );
    mLine.draw();
    ofSetColor( 0, 255, 255 );
    for( ofVec2f point : mLine.getVertices() ) {
        ofCircle( point.x, point.y, 2 );
    }
    ofCircle(100, 100, 50);
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
    cout << mLine.size() << endl;
    for( ofVec2f point : mLine.getVertices() ) {
        cout << "   " << point << endl;
    }
    ctr++;
    pts[ctr] = ofVec2f( x, y );
    
    if (ctr == 4)
    {
        //cout << "draw" << endl;
        pts[3] = ofVec2f((pts[2].x + pts[4].x)/2.0, (pts[2].y + pts[4].y)/2.0);
        // move the endpoint to the middle of the line joining the second control point
        // of the first Bezier segment and the first control point of the second Bezier segment
        
        nvgluBindFramebuffer( fb );
        mNanoVG->beginFrame( mCanvasSize.x, mCanvasSize.y, 1 );
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
        
        mNanoVG->beginPath();
        mNanoVG->circle( x, y, 2 );
        
        mNanoVG->strokeColor( ofFloatColor( 1, 0, 0, 1 ) );
        mNanoVG->strokeWidth( 4 );
        mNanoVG->stroke();
        
        mNanoVG->endFrame();
        nvgluBindFramebuffer(NULL);
        
        //[self setNeedsDisplay];
        // replace points and get ready to handle the next segment
        pts[0] = pts[3];
        pts[1] = pts[4];
        ctr = 1;
    } else {
        nvgluBindFramebuffer( fb );
        mNanoVG->beginFrame( mCanvasSize.x, mCanvasSize.y, 1 );
        mNanoVG->beginPath();
        
        mNanoVG->circle( x, y, 2 );
        
        mNanoVG->strokeColor( ofFloatColor( 1, 0, 0, 1 ) );
        mNanoVG->strokeWidth( 4 );
        mNanoVG->stroke();
        mNanoVG->endFrame();
        
        nvgluBindFramebuffer(NULL);
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    ctr = 0;
    pts[0] = ofVec2f( x, y );
    
    mLine.addVertex( x, y );
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