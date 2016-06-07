#pragma once
#ifndef VILAINCORE_H
#define VILAINCORE_H

#include <ofMain.h>
#include <ofxOsc.h>
#include <ofxOscRouter.h>

#include "vilain.h"

namespace vilain
{
class vilainCore :
    public ofBaseApp,
    public ofxOscRouter
{
public:
    vilainCore():
        ofBaseApp(),
        ofxOscRouter("vilain", 9876),
        bDebug(false),
        bBlackOut(false)
    {
        ofxOscRouterNode::addOscMethod("exit");
        ofxOscRouterNode::addOscMethod("debug");
        ofxOscRouterNode::addOscMethod("blackout");
    };
    void setup();
    void update();
    void draw();
    void exit();

    void processOscCommand(const std::string& command, const ofxOscMessage& m);

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);

private:
    ofxOscMessage m;
    ofxOscSender oscSend;
    bool bDebug;
    bool bBlackOut;
};
};
#endif

