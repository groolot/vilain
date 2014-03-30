#pragma once
#ifndef VILAINAPP_H
#define VILAINAPP_H

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

    shared_ptr<vilainImage> addNewImageFromFile(string path_to_file);
    shared_ptr<vilainImage> addNewImageFromFile(ofFile file);
    shared_ptr<vilainImage> addNewImageFromFiles(vector<ofFile> list_of_files);

protected:
    shared_ptr<vilainImage> oneImage;     /**< Pointer to the last added vilainImage ? */
    vector<shared_ptr<vilainImage>> imagesCollection;

    shared_ptr<vilainFlux> oneFlux;       /**< Pointer to the last added vilainFlux ? */
    vector<shared_ptr<vilainFlux>> fluxCollection;

    bool bInfoText = True;
    int lastMouseX=0, lastMouseY=0;
};
}
#endif // VILAINAPP_H
