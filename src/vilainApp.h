#pragma once

#include <ofMain.h>
//#include <ofxControlPanel.h>

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

    vilainImage * addNewImageFromFile(string path_to_file);
    vilainImage * addNewImageFromFiles(vector<string> paths_to_files);

protected:
    vilainImage * oneImage;     /**< Pointer to the last added vilainImage ? */
    vector<vilainImage *> imagesCollection;

    vilainFlux * oneFlux;       /**< Pointer to the last added vilainFlux ? */
    vector<vilainFlux *> fluxCollection;

    bool bInfoText = True;
    int lastMouseX=0, lastMouseY=0;
};
