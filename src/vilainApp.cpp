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
#include "vilainApp.h"

using namespace vilain;

//--------------------------------------------------------------
void vilainApp::setup()
{
    xmlFileSerialize.loadFile("vilain-save.xml");
    const char* name = glfwGetMonitorName(glfwGetPrimaryMonitor());
    ofLogNotice(PROG_NAME) << _("Primary monitor: ") << name << endl;
    vector <ofFile> files;
    files.push_back(ofFile("groolot.jpg"));
    files.push_back(ofFile("groolot.png"));

    vector<ofVideoDevice> devicesID = grabber.listDevices();

    ofSetupScreen();
    ofSetFrameRate(30);
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofLog() << "\t" PROG_NAME ;
    ofDisableArbTex();

    addNewImageFromFiles(files);

    for(ofVideoDevice deviceID : devicesID)
        addNewFlux(deviceID.id, 160, 120);
    // TODO: implement with a pointer to vilainFlux
    // example: addNewFlux(new vilainFlux(ID, w, h))

    // Positioning / Sizing
    for(ofPtr<vilainObject> obj : allObjects)
        obj->setPosition(ofGetWindowWidth()/2. , ofGetWindowHeight()/2. , 0);

    ofxFensterManager::get()->setupWindow(&ControlWindow);
    ControlWindow.allObjects = &allObjects;
}

//--------------------------------------------------------------
void vilainApp::update()
{
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void vilainApp::draw()
{
    ofSetColor(ofColor::white);
    for(ofPtr<vilainObject> obj : allObjects)
        obj->draw();

    // OnScreenDraw text information
    // TODO: will be deprecated sooner and replaced with
    // a beautiful GUI information box :)
    if(bInfoText)
    {
        stringstream ss;
        ss << "Framerate: " << ofToString(ofGetFrameRate(),0) << endl;
        ss << "(t): Info Text" << endl;
        if(bEditMode)
        {
            ss << "Selected object: " << (* selectedObject) << endl;
        }
        ofDrawBitmapString(ss.str(), 20, 20);
    }
}

//--------------------------------------------------------------
void vilainApp::keyPressed(int key)
{
    ofLogVerbose(PROG_NAME) << _("Keypressed: ") << key;
    if(key=='t') // Show the textual information box
        bInfoText = !bInfoText;
    else if(key=='1')
    {
        (* selectedObject)->setResolution(2., 2.);
    }
    else if(key=='2')
    {
        (* selectedObject)->setResolution(3., 3.);
    }
    else if(key=='3')
    {
        (* selectedObject)->setResolution(4., 4.);
    }
    else if(key==127) // Suppr
    {
        if(bEditMode and selectedObject != allObjects.end())
        {
            (* selectedObject)->leaveMe();
            selectedObject = allObjects.erase(selectedObject);
            if(selectedObject == allObjects.end()) selectedObject = allObjects.begin();
            (* selectedObject)->catchMe(bEditMode);
        }
    }
    else if(key==358) // Right Arrow
    {
        SelectNextObject();
    }
    else if(key==356) // Left Arrow
    {
        SelectPreviousObject();
    }
    else if(key==9) // TAB
    {
        bEditMode = !bEditMode;
        (* selectedObject)->catchMe(bEditMode);
    }
}

//--------------------------------------------------------------
void vilainApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void vilainApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void vilainApp::mouseDragged(int x, int y, int button)
{
    if(button == OF_MOUSE_BUTTON_1)
    {
        (* selectedObject)->mouseDragged(x, y, button);
    }
    else if(button == OF_MOUSE_BUTTON_2)
    {
        mouseDistance = ofVec2f(x, y) - mousePressedPosition;
        ofVec2f futurPosition = objectPressedPosition + mouseDistance;
        (* selectedObject)->mouseDragged(futurPosition.x, futurPosition.y, button);
    }
    ofLogVerbose(PROG_NAME) << _("mouseDragged: ") << x << "," << y;
}

//--------------------------------------------------------------
void vilainApp::mousePressed(int x, int y, int button)
{
    mousePressedPosition = ofVec2f(x,y);
    objectPressedPosition.x = (* selectedObject)->getX();
    objectPressedPosition.y = (* selectedObject)->getY();
}

//--------------------------------------------------------------
void vilainApp::mouseReleased(int x, int y, int button)
{
    mouseReleasedPosition = ofVec2f(x,y);
}

//--------------------------------------------------------------
void vilainApp::windowResized(int w, int h)
{
    ofLogVerbose(PROG_NAME) << _("Resize main window to: ") << w << "x" << h;
}

//--------------------------------------------------------------
void vilainApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void vilainApp::dragEvent(ofDragInfo dragInfo)
{

}

//--------------------------------------------------------------
void vilainApp::exit()
{

}

/** \brief Cycle to the next object in the allObjects vector
 *
 * \pre Selected object must not be null
 */
void vilainApp::SelectNextObject()
{
    if(selectedObject != allObjects.end())
    {
        (* selectedObject)->leaveMe();
        if(selectedObject + 1 == allObjects.end())
            selectedObject = allObjects.begin();
        else
            selectedObject++;
        (* selectedObject)->catchMe(bEditMode);
    }
}

/** \brief Cycle to the previous object in the allObjects vector
 *
 * \pre Selected object must not be null
 */
void vilainApp::SelectPreviousObject()
{
    if(selectedObject != allObjects.end())
    {
        (* selectedObject)->leaveMe();
        if(selectedObject == allObjects.begin())
            selectedObject = allObjects.end() - 1;
        else
            selectedObject--;
        (* selectedObject)->catchMe(bEditMode);
    }
}

//--------------------------------------------------------------
void vilainApp::addNewImageFromFile(string path_to_file)
{
    ofPtr<vilainImage> curImage( new vilainImage(path_to_file) );
    curImage->resizeToTexture(curImage->image.getTextureReference());
    allObjects.push_back(curImage);
    selectedObject = allObjects.begin();
    char logMessage[256];
    /*TRANSLATORS: The %s is replaced at runtime by the file path.
    	Please keep it in your translation, wherever you want.
    	Maximum number of characters : 255
    */
    sprintf(logMessage, _("Add file %s as a new vilainImage layer of size: "), path_to_file.c_str());
    ofLogVerbose(PROG_NAME) << logMessage
                            << curImage->image.getTextureReference().getWidth()
                            << "x"
                            << curImage->image.getTextureReference().getHeight();
}

//--------------------------------------------------------------
void vilainApp::addNewImageFromFile(ofFile file)
{
    addNewImageFromFile(file.path());
}

//--------------------------------------------------------------
void vilainApp::addNewImageFromFiles(vector<ofFile> list_of_files)
{
    for(ofFile file : list_of_files)
        addNewImageFromFile(file);
}

void vilainApp::addNewFlux(int deviceID, int w, int h)
{
    ofPtr<vilainFlux> curFlux( new vilainFlux(deviceID, w, h));
    allObjects.push_back(curFlux);
    selectedObject = allObjects.begin();
}
