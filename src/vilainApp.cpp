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

/** \brief Setup the application. Similar to constructor.
 *
 * \return void
 *
 */
void vilainApp::setup()
{
    xmlFileSerialize.loadFile("vilain-save.xml");
    const char* name = glfwGetMonitorName(glfwGetPrimaryMonitor());
    ofLogNotice(PROG_NAME) << _("Primary monitor: ") << name << endl;
    vector <ofFile> files;
    files.push_back(ofFile("groolot.jpg"));
    files.push_back(ofFile("groolot.png"));

    vector<ofVideoDevice> devicesID = grabber.listDevices();

    ofSetFrameRate(30);
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofLog() << "\t" PROG_NAME ;

    for(ofVideoDevice deviceID : devicesID)
        addNewFlux(deviceID.id, 160, 120);

    addNewImageFromFiles(files);

    // TODO: implement with a pointer to vilainFlux
    // example: addNewFlux(new vilainFlux(ID, w, h))

    // Positioning
    for(ofPtr<vilainObject> obj : allObjects)
        obj->setPosition(ofGetWindowWidth() / 2. , ofGetWindowHeight() / 2. , 0);
}

//--------------------------------------------------------------
void vilainApp::update()
{
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void vilainApp::draw()
{
	ofBackground(0);
    ofSetupScreenOrtho(ofGetViewportWidth(), ofGetViewportHeight(), -1., std::numeric_limits<float>::max());
    ofEnableDepthTest();
    ofSetColor(ofColor::white);

    for(ofPtr<vilainObject> obj : allObjects)
        obj->draw();

    // OnScreenDraw text information
    // TODO: will be deprecated sooner and replaced with
    // a beautiful GUI information box :)
    if(bInfoText)
    {
        stringstream ss;
        ss << "Framerate: " << ofToString(ofGetFrameRate(), 0) << endl;
        ss << "(t): Info Text" << endl;

        if(bEditMode)
        {
            ss << "Selected object: " << (* selectedObject) << endl;
            ss << "z-Index: " << (* selectedObject)->getZ();
        }
		glDepthFunc(GL_ALWAYS);
        ofDrawBitmapString(ss.str(), 20, 20);
        glDepthFunc(GL_LESS);
    }
}

//--------------------------------------------------------------
void vilainApp::keyPressed(int key)
{
    // Edit/Design Mode
    if(bEditMode)
    {
        (* selectedObject)->keyPressed(key);/**< Send keyPressed event to selected object */

        if(key == OF_KEY_DEL)
        {
            if(selectedObject != allObjects.end())
            {
                (* selectedObject)->leaveMe();
                selectedObject = allObjects.erase(selectedObject);

                if(selectedObject == allObjects.end()) selectedObject = allObjects.begin();

                (* selectedObject)->catchMe(bEditMode);
            }
        }
        else if(key == OF_KEY_RIGHT)
        {
            SelectNextObject();
        }
        else if(key == OF_KEY_LEFT)
        {
            SelectPreviousObject();
        }
    }
    // Performance mode
    else
    {

    }

    // Always
    ofLogVerbose(PROG_NAME) << _("Keypressed: ") << key;

    if(key == 't') // Show the textual information box
        bInfoText = !bInfoText;

    else if(key == OF_KEY_TAB)
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
    (* selectedObject)->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void vilainApp::mousePressed(int x, int y, int button)
{
    (* selectedObject)->mousePressed(x, y, button);
}

//--------------------------------------------------------------
void vilainApp::mouseReleased(int x, int y, int button)
{

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
    ofPtr<vilainImage> curImage(new vilainImage(path_to_file));
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
    ofPtr<vilainFlux> curFlux(new vilainFlux(deviceID, w, h));
    allObjects.push_back(curFlux);
    selectedObject = allObjects.begin();
}
