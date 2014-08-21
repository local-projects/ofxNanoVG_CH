#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){

	//ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context
    ofAppGLFWWindow win;
    win.setNumSamples( 0 );
    //win.setDoubleBuffering(false);
    //win.setOrientation(OF_ORIENTATION_90_LEFT);
    //win.setMultiDisplayFullscreen(true);
    //win.set
    
    ofSetupOpenGL( &win, 450, 450, OF_WINDOW );// <-------- setup the GL context
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());
}
