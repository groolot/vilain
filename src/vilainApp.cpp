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
    ofLogNotice("MONITOR") << name << endl;
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
    {
        ofPtr<vilainFlux> oneFlux( new vilainFlux(deviceID.id) );
        oneFlux->init(160,120);
        fluxCollection.push_back(oneFlux);
    }

    // Positionning / Sizing
    for(ofPtr<vilainImage> oneImage : imagesCollection)
        oneImage->setPosition(ofGetWindowWidth()/2. , ofGetWindowHeight()/2. , 0);
    for(ofPtr<vilainFlux> oneFlux : fluxCollection)
        oneFlux->setPosition(ofGetWindowWidth()/2. , ofGetWindowHeight()/2. , 0);

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
    for(ofPtr<vilainImage> oneImage : imagesCollection)
        oneImage->draw();
    for(ofPtr<vilainFlux> oneFlux : fluxCollection)
        oneFlux->draw();

    if(bInfoText)
    {
        stringstream ss;
        ss << _("Framerate: ") << ofToString(ofGetFrameRate(),0) << "\n";
        ss << _("(t): Info Text") << endl;
        ofDrawBitmapString(ss.str().c_str(), 20, 20);
    }
}

//--------------------------------------------------------------
void vilainApp::keyPressed(int key)
{
    if(key=='t')
        bInfoText = !bInfoText;
    else if(key==9) // TAB
    {
        for(ofPtr<vilainImage> oneImage : imagesCollection)
            oneImage->setEditMode(!oneImage->isEditing());
        for(ofPtr<vilainFlux> oneFlux : fluxCollection)
            oneFlux->setEditMode(!oneFlux->isEditing());
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
    fluxCollection[0]->mouseDragged(x, y, button);
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
    // Re-Positionning
    for(ofPtr<vilainImage> oneImage : imagesCollection)
        oneImage->setPosition(ofGetWindowWidth()/2. , ofGetWindowHeight()/2. , 0);
    for(ofPtr<vilainFlux> oneFlux : fluxCollection)
        oneFlux->setPosition(ofGetWindowWidth()/2. , ofGetWindowHeight()/2. , 0);
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
    ofPtr<vilainImage> oneImage( new vilainImage(path_to_file) );
    oneImage->resizeToTexture(oneImage->image.getTextureReference());
    imagesCollection.push_back(oneImage);
    ofLogVerbose("vilainApp::addNewImageFromFile")
            << _("Add file ")
            << path_to_file
            << _(" as new vilainImage layer of size ")
            << oneImage->image.getTextureReference().getWidth()
            << "x"
            << oneImage->image.getTextureReference().getHeight();
    return oneImage;
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
        oneImage = addNewImageFromFile(file);
    return oneImage;
}

