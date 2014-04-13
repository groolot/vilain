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
    GLFWmonitor* primary = glfwGetPrimaryMonitor();
    const char* name = glfwGetMonitorName(primary);
    ofLogNotice(PROG_NAME) << _("Current monitor: ") << name << endl;
    vector <ofFile> files;
    files.push_back(ofFile("groolot.jpg"));
    files.push_back(ofFile("groolot.png"));

    vector<ofVideoDevice> devicesID = grabber.listDevices();

    ofSetupScreen();
    ofSetFrameRate(30);
    ofLog() << "\t" PROG_NAME ;
    ofDisableArbTex();

    addNewImageFromFiles(files);

    for(ofVideoDevice deviceID : devicesID)
        addNewFlux(deviceID.id, 160, 120);
        // TODO: implement with a pointer to vilainFlux
        // example: addNewFlux(new vilainFlux(ID, w, h))

    // Positionning / Sizing
    for(ofPtr<vilainImage> curImage : imagesCollection)
        curImage->setPosition(ofGetWindowWidth()/2. , ofGetWindowHeight()/2. , 0);
    for(ofPtr<vilainFlux> curFlux : fluxCollection)
        curFlux->setPosition(ofGetWindowWidth()/2. , ofGetWindowHeight()/2. , 0);

    // TODO: implement this!
    selectedObject = lastImage;

    ofxFensterManager::get()->setupWindow(&ControlWindow);
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
    for(ofPtr<vilainImage> curImage : imagesCollection)
        curImage->draw();
    for(ofPtr<vilainFlux> curFlux : fluxCollection)
        curFlux->draw();

    // OnScreenDraw text information
    // TODO: will be deprecated sooner and replaced with
    // a beautiful GUI information box :)
    if(bInfoText)
    {
        stringstream ss;
        ss << "Framerate: " << ofToString(ofGetFrameRate(),0) << "\n";
        ss << "(t): Info Text" << endl;
        ofDrawBitmapString(ss.str().c_str(), 20, 20);
    }
}

//--------------------------------------------------------------
void vilainApp::keyPressed(int key)
{
    ofLogVerbose(PROG_NAME) << _("Keypressed: ") << key << endl;
    if(key=='t')
        bInfoText = !bInfoText;
    else if(key=='1')
        selectedObject->setResolution(2., 2.);
    else if(key=='2')
        selectedObject->setResolution(3., 3.);
    else if(key=='3')
        selectedObject->setResolution(4., 4.);
	else if(key==358) // Right Arrow
		selectedObject = lastFlux;
	else if(key==359) // Bottom Arrow
		selectedObject = lastImage;
    else if(key==9) // TAB
    {
        selectedObject->setEditMode(!selectedObject->isEditing());
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
    selectedObject->mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void vilainApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void vilainApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void vilainApp::windowResized(int w, int h)
{
    ofLogVerbose(PROG_NAME) << _("Resize main window to: ") << w << "x" << h << endl;
    // Re-Positionning
    for(ofPtr<vilainImage> curImage : imagesCollection)
        curImage->setPosition(ofGetWindowWidth()/2. , ofGetWindowHeight()/2. , 0);
    for(ofPtr<vilainFlux> curFlux : fluxCollection)
        curFlux->setPosition(ofGetWindowWidth()/2. , ofGetWindowHeight()/2. , 0);
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

//--------------------------------------------------------------
ofPtr<vilainImage> vilainApp::addNewImageFromFile(string path_to_file)
{
    ofPtr<vilainImage> curImage( new vilainImage(path_to_file) );
    curImage->resizeToTexture(curImage->image.getTextureReference());
    imagesCollection.push_back(curImage);
    allObjects.push_back(curImage);
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
    return curImage;
}

//--------------------------------------------------------------
ofPtr<vilainImage> vilainApp::addNewImageFromFile(ofFile file)
{
    return addNewImageFromFile(file.path());
}

//--------------------------------------------------------------
ofPtr<vilainImage> vilainApp::addNewImageFromFiles(vector<ofFile> list_of_files)
{
    for(ofFile file : list_of_files)
        lastImage = addNewImageFromFile(file);
    return lastImage;
}

ofPtr<vilainFlux> vilainApp::addNewFlux(int deviceID, int w, int h)
{
	ofPtr<vilainFlux> curFlux( new vilainFlux(deviceID, w, h));
    fluxCollection.push_back(curFlux);
    allObjects.push_back(curFlux);
    lastFlux = curFlux;
    return curFlux;
}
