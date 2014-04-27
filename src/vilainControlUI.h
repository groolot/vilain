#ifndef VILAINCONTROLUI_H_INCLUDED
#define VILAINCONTROLUI_H_INCLUDED

#include <ofMain.h>
#include "ofxFensterManager.h"
#include "ofxTimeline.h"

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
        setWindowTitle("Control Window");
        ofEnableSmoothing();
        ofEnableAlphaBlending();

        timeline.setup();
        timeline.setLoopType(OF_LOOP_NORMAL);
        timeline.setDurationInSeconds(30);

        //this is the simplest example and is really flexible
        timeline.addLFO("LFO");
    }

    void update()
    {
        radius = sin(ofGetFrameNum()*.06)*100;
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

        if(b_VisibleTimeline)
            timeline.draw();

        for(ofPtr<vilainObject> obj : *allObjects)
            obj->draw();
    }

    void keyPressed(int key)
    {
        if(key == 't')
            b_VisibleTimeline = !b_VisibleTimeline;
    }

    void keyReleased(int key)
    {

    }

    float radius;
    ofxTimeline timeline;
    bool b_VisibleTimeline = false;
    vector<ofPtr<vilainObject>> * allObjects;
};
}

#endif // VILAINCONTROLUI_H_INCLUDED
