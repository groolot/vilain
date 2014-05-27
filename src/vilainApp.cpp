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
    files.push_back(ofFile("groolot.png"));
    files.push_back(ofFile("groolot.jpg"));

    vector<ofVideoDevice> devicesID = grabber.listDevices();

    ofSetFrameRate(30);
    ofSetRectMode(OF_RECTMODE_CORNER);
    ofEnableAlphaBlending();
    ofLog() << "\t" PROG_NAME ;

    for(ofVideoDevice deviceID : devicesID)
    {
        addNewFlux(deviceID.id, 160, 120);
    }

    addNewImageFromFiles(files);

    // TODO: implement with a pointer to vilainFlux
    // example: addNewFlux(new vilainFlux(ID, w, h))

    // Positioning
    for(ofPtr<vilainObject> obj : allObjects)
    {
        obj->setPosition(ofGetWindowWidth() / 2. , ofGetWindowHeight() / 2. , 0);
        allObjectsName.push_back(obj->getName());
    }

    vilainApp::setMainUI();
}

//--------------------------------------------------------------
void vilainApp::update()
{
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void vilainApp::draw()
{
    vilainApp::drawProjector();
}

//--------------------------------------------------------------
void vilainApp::drawProjector()
{
    ofBackground(100);
    ofSetupScreenOrtho(ofGetViewportWidth(), ofGetViewportHeight(), -1., std::numeric_limits<float>::max());
    ofEnableDepthTest();

    ofSetColor(ofColor::white);

    for(ofPtr<vilainObject> obj : allObjects)
    {
        obj->draw();
        obj->drawObjectUI();
    }

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
        ofDrawBitmapString(ss.str(), 20, ofGetHeight() - 60);
        glDepthFunc(GL_LESS);
    }
}

//--------------------------------------------------------------
void vilainApp::setMainUI()
{
    tabBar = new ofxUITabBar; /** Tab bar initialization */

    projectSettingsTab->setName("Project settings"); /** Set tab name */
    projectSettingsTab->addLabel("Project settings"); /** Set title */
    projectSettingsTab->addSpacer();
    projectSettingsTab->addLabelButton("Save settings", false); /** Button to save settings */
    projectSettingsTab->addLabelButton("Load settings", false); /** Button to load saved settings */

    ofAddListener(projectSettingsTab->newGUIEvent, this, &vilainApp::mainUI_Event); /** Listener to wait new events */
    projectSettingsTab->autoSizeToFitWidgets(); /** Auto height size */
    tabBar->addCanvas(projectSettingsTab);
    mainUI.push_back(projectSettingsTab); /** Add the tab to the main canvas */

    objectManagementTab->setName("Object management"); /** Set tab name */
    objectManagementTab->addLabel("Object management"); /** Set title */
    objectManagementTab->addSpacer();
    objectList = objectManagementTab->addRadio("Object list", allObjectsName); /** Object listing */
    objectList->activateToggle((* selectedObject)->getName());
    objectManagementTab->addSpacer();
    objectManagementTab->addTextInput("New object name", "Add a new object"); /** Text input box to add new object */
    objectManagementTab->addSpacer();
    objectManagementTab->addLabelButton("Delete selected object", false); /** Button to delte selected object */
    objectManagementTab->addSpacer();
    objectManagementTab->addLabelButton("list", false);

    ofAddListener(objectManagementTab->newGUIEvent, this, &vilainApp::mainUI_Event); /** Listener to wait new events */
    objectManagementTab->autoSizeToFitWidgets(); /** Auto height size */
    tabBar->addCanvas(objectManagementTab);
    mainUI.push_back(objectManagementTab); /** Add the tab to the main canvas */
}

//--------------------------------------------------------------
void vilainApp::mainUI_Event(ofxUIEventArgs &e)
{
    string eventName = e.getName();

    cout << eventName << endl;

    if(eventName == "Object list")
    {
        bool activateEdition = (* selectedObject)->isEditing();

        (* selectedObject)->leaveMe();
        ofxUIRadio *ObjectList = (ofxUIRadio *) e.widget;
        selectedObject = (allObjects.begin() + ObjectList->getValue());
        (* selectedObject)->catchMe(activateEdition);
    }

    if(eventName == "New object name")
    {
        ofxUITextInput *newObject = (ofxUITextInput *) e.widget;

        if(newObject->getTextString() != "Add a new object")
        {
            allObjectsName.push_back(newObject->getTextString());
        }
    }

    if(eventName == "New object name")
    {
        ofxUIRadio *ObjectList = (ofxUIRadio *) e.widget;
        allObjectsName.erase(allObjectsName.begin() + ObjectList->getValue());
    }

    if(eventName == "list") {}
}

//--------------------------------------------------------------
void vilainApp::keyPressed(int key)
{
    // Edit/Design Mode
    if(bEditMode)
    {
        (* selectedObject)->keyPressed(key);/**< Send keyPressed event to selected object */
        std::sort(allObjects.begin(), allObjects.end(), vilainObject());

        if(key == OF_KEY_DEL)
        {
            if(selectedObject != allObjects.end())
            {
                (* selectedObject)->leaveMe();
                selectedObject = allObjects.erase(selectedObject);

                if(selectedObject == allObjects.end())
                {
                    selectedObject = allObjects.begin();
                }

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
        if(key == ' ')
        {
            addNewImageFromFile("groolot.jpg");
        }
    }

    // Always
    ofLogVerbose(PROG_NAME) << _("Keypressed: ") << key;
    ofLogVerbose(PROG_NAME) << (* selectedObject)->getZ();

    if(key == 't') // Show the textual information box
    {
        bInfoText = !bInfoText;
    }

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
        {
            selectedObject = allObjects.begin();
        }
        else
        {
            selectedObject++;
        }

        (* selectedObject)->catchMe(bEditMode);
        objectList->activateToggle((* selectedObject)->getName());
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
        {
            selectedObject = allObjects.end() - 1;
        }
        else
        {
            selectedObject--;
        }

        (* selectedObject)->catchMe(bEditMode);
        objectList->activateToggle((* selectedObject)->getName());
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
    {
        addNewImageFromFile(file);
    }
}

/** \brief Add a new video grabber (webcam, video device, etc.) to the global objects list
 *
 * \param deviceID int The ID number of the device
 * \param w int Width of the allocated surface
 * \param h int Height of the allocated surface
 * \return void
 *
 */
void vilainApp::addNewFlux(int deviceID, int w, int h)
{
    ofPtr<vilainFlux> curFlux(new vilainFlux(deviceID, w, h));
    allObjects.push_back(curFlux);
    selectedObject = allObjects.begin();
}
