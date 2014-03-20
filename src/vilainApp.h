#pragma once

#include <ofMain.h>
#include "vilainImage.h"
#include "vilainFlux.h"

class vilainApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

protected:
    vilainImage * oneImage;
    vector<vilainImage *> imagesCollection;

    vilainFlux * oneFlux;
    vector<vilainFlux *> fluxCollection;

    bool bInfoText = True;
};
