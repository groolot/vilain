#include "vilainApp.h"
#include <GLFW/glfw3.h>

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
        shared_ptr<vilainFlux> oneFlux( new vilainFlux(deviceID.id) );
        oneFlux->init(160,120);
        fluxCollection.push_back(oneFlux);
    }

    // Positionning
    for(shared_ptr<vilainImage> oneImage : imagesCollection)
        oneImage->setPosition(ofGetWindowWidth()/2. , ofGetWindowHeight()/2. , 0);
    for(shared_ptr<vilainFlux> oneFlux : fluxCollection)
        oneFlux->setPosition(ofGetWindowWidth()/2. , ofGetWindowHeight()/2. , 0);

	ofxFensterManager::get()->setupWindow(&ControlWindow);
}

//--------------------------------------------------------------
void vilainApp::update()
{
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
//    for(auto oneImage : this->imagesCollection)
//        oneImage->setPosition(mouseX,mouseY,0);
//    for(auto oneFlux : this->fluxCollection)
//    {
//        if(lastMouseX!=mouseX || lastMouseY!=mouseY)
//        {
//            lastMouseX = mouseX;
//            lastMouseY = mouseY;
//            oneFlux->setPosition(mouseX,mouseY,0);
//        }
//    }
}

//--------------------------------------------------------------
void vilainApp::draw()
{
    ofSetColor(ofColor::white);
    for(shared_ptr<vilainImage> oneImage : imagesCollection)
        oneImage->draw();
    for(shared_ptr<vilainFlux> oneFlux : fluxCollection)
        oneFlux->draw();

    ofMesh mesh = fluxCollection[0]->getMesh();
    int n = mesh.getNumVertices();

    ofVec2f mouse(mouseX, mouseY);
    glPointSize(10.);
    mesh.drawVertices();
    mesh.drawWireframe();

	for(int i = 0; i < n; i++) {
		ofVec3f cur = mesh.getVertex(i);
		float distance = cur.distance(mouse);
		if(i == 0 || distance < nearestDistance) {
			nearestDistance = distance;
			nearestVertex = cur;
			nearestIndex = i;
		}
	}

	ofSetColor(ofColor::gray);
	ofLine(nearestVertex, mouse);

	ofFill();
	ofSetColor(ofColor::yellow);
	ofSetLineWidth(2);
	ofCircle(nearestVertex, 4);
	ofSetLineWidth(1);

	ofVec2f offset(10, -10);
	ofDrawBitmapStringHighlight(ofToString(nearestIndex), mouse + offset);


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
    fluxCollection[0]->getMeshPtr()->setVertex(nearestIndex, ofVec3f(mouseX, mouseY));
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
    for(shared_ptr<vilainImage> oneImage : imagesCollection)
        oneImage->setPosition(ofGetWindowWidth()/2. , ofGetWindowHeight()/2. , 0);
    for(shared_ptr<vilainFlux> oneFlux : fluxCollection)
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

