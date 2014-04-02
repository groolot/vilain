#pragma once
#ifndef VILAINAPP_H
#define VILAINAPP_H

#include <libintl.h>
#define _(String) gettext(String)
#define _N(String) String

#include <ofMain.h>
#include <memory>

#include "vilainImage.h"
#include "vilainFlux.h"

namespace vilain
{
class vilainApp : public ofBaseApp
{
public:
    void setup() override;
    void update() override;
    void draw() override;

    void keyPressed(int key) override;
    void keyReleased(int key) override;
    void mouseMoved(int x, int y) override;
    void mouseDragged(int x, int y, int button) override;
    void mousePressed(int x, int y, int button) override;
    void mouseReleased(int x, int y, int button) override;
    void windowResized(int w, int h) override;
    void dragEvent(ofDragInfo dragInfo) override;
    void gotMessage(ofMessage msg) override;
    void exit() override;

    ofPtr<vilainImage> addNewImageFromFile(string path_to_file);
    ofPtr<vilainImage> addNewImageFromFile(ofFile file);
    ofPtr<vilainImage> addNewImageFromFiles(vector<ofFile> list_of_files);

protected:
    ofPtr<vilainImage> oneImage;     /**< Pointer to the last added vilainImage ? */
    vector<ofPtr<vilainImage>> imagesCollection;

    ofPtr<vilainFlux> oneFlux;       /**< Pointer to the last added vilainFlux ? */
    vector<ofPtr<vilainFlux>> fluxCollection;

    bool bInfoText = True;
    int lastMouseX=0, lastMouseY=0;

    ofVideoGrabber grabber;

    float nearestDistance = 0;
    ofVec2f nearestVertex;
    int nearestIndex = 0;

};
}
#endif // VILAINAPP_H
