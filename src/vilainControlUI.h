#ifndef VILAINCONTROLUI_H_INCLUDED
#define VILAINCONTROLUI_H_INCLUDED

#include <ofMain.h>
#include "ofxFensterManager.h"

#include "vilainImage.h"

namespace vilain
{
class vilainControlUI : public ofxFenster
{
public:
    void setup()
    {
        setWindowShape(1280, 720);
        setWindowPosition(0, 0);
        setWindowTitle("Control");
        ofEnableSmoothing();
        ofEnableAlphaBlending();
    }

    void update()
    {
        radius = sin(ofGetFrameNum() * .06) * 100;
    }

    void draw()
    {
        ofBackground(0);

        ofNoFill();

        ofSetColor(100);
        ofLine(mouseX, 0, mouseX, getHeight());
        ofLine(0, mouseY, getWidth(), mouseY);

        ofSetColor(255);
        ofCircle(getWidth()*.5, getHeight()*.5, radius);
    }

    void keyPressed(int key)
    {

    }

    void keyReleased(int key)
    {

    }

    float radius;
};
}

#endif // VILAINCONTROLUI_H_INCLUDED
