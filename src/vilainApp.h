/*
 * vilain::, a set of visual object for video mapping and light light show
 *     Copyright (C) 2014 Gregory DAVID <groolot@groolot.net>
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef VILAINAPP_H
#define VILAINAPP_H

#include <ofMain.h>
#include <ofxFensterManager.h>
#include <ofxXmlSettings.h>

#include "vilain.h"
#include "vilainControlUI.h"
#include "vilainObject.h"
#include "vilainImage.h"
#include "vilainFlux.h"

namespace vilain
{
/** \brief Main program
 */
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

    void SelectNextObject();
    void SelectPreviousObject();

    void addNewImageFromFile(string path_to_file);
    void addNewImageFromFile(ofFile file);
    void addNewImageFromFiles(vector<ofFile> list_of_files);
    void addNewFlux(int deviceID, int w, int h);

    ofxXmlSettings xmlFileSerialize;

    bool bEditMode = False; /**< Application edit mode flag \li \c true for editing, \li \c false (default) for performing */

protected:
    vector<ofPtr<vilainImage>> imagesCollection;/**< Pointer to vilainImage container */
    vector<ofPtr<vilainFlux>> fluxCollection;/**< Pointer to vilainFlux container */

    vector<ofPtr<vilainObject>> allObjects;/**< Pointer to the container of all objects */
    vector<ofPtr<vilainObject>>::iterator selectedObject;/**< Iterator on allObjects container, point to the selected object pointer */

    bool bInfoText = True;

    vilainControlUI ControlWindow;
private:
    ofVideoGrabber grabber;
};
}
#endif // VILAINAPP_H

