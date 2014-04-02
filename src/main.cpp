#include <ofMain.h>

#include "ofxFensterManager.h"

#include "vilainApp.h"

//========================================================================
int main( )
{
    setlocale(LC_ALL, "");
    bindtextdomain(PROG_NAME, ".");
    textdomain(PROG_NAME);
    ofSetLogLevel(PROG_NAME,OF_LOG_NOTICE);
    //ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

	ofxFensterManager::setup(1024,768,OF_WINDOW);

    ofRunApp( new vilain::vilainApp());

}
