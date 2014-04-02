#include <ofMain.h>

#include "vilainApp.h"

//========================================================================
int main( )
{
    setlocale(LC_ALL, "");
    bindtextdomain("vilain", ".");
    textdomain("vilain");
    ofSetLogLevel("vilain",OF_LOG_NOTICE);
    ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp( new vilain::vilainApp());

}
