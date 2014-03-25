#include "vilainApp.h"

using namespace vilain;

//--------------------------------------------------------------
void vilainApp::setup()
{
    vector <ofFile> files;
    files.push_back(ofFile("groolot.jpg"));
    files.push_back(ofFile("groolot.png"));

    vector<int> devicesID;
    devicesID.push_back(0);

    ofSetupScreen();
    ofSetFrameRate(30);
    ofLog() << "\tvilain::Mapping";
    ofDisableArbTex();

    this->addNewImageFromFiles(files);

    for(auto deviceID : devicesID)
    {
        oneFlux = new vilainFlux(deviceID);
        oneFlux->init(80,60);
        this->fluxCollection.push_back(oneFlux);
    }
}

//--------------------------------------------------------------
void vilainApp::update()
{
    for(auto oneImage : this->imagesCollection)
        oneImage->setPosition(mouseX,mouseY,0);
    for(auto oneFlux : this->fluxCollection)
    {
        if(lastMouseX!=mouseX || lastMouseY!=mouseY)
        {
            lastMouseX = mouseX;
            lastMouseY = mouseY;
            oneFlux->setPosition(mouseX,mouseY,0);
        }
    }
}

//--------------------------------------------------------------
void vilainApp::draw()
{
    for(auto uneImage : this->imagesCollection)
        uneImage->draw();
    for(auto oneFlux : this->fluxCollection)
        oneFlux->draw();

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
vilainImage * vilainApp::addNewImageFromFile(string path_to_file)
{
    this->oneImage = new vilainImage(path_to_file);
    //this->oneImage->resizeToTexture(oneImage->image.getTextureReference());
    this->imagesCollection.push_back(oneImage);
    ofLogVerbose("vilainApp::addNewImageFromFile")
            << "Add file "
            << path_to_file
            << " as new vilainImage layer of size "
            << this->oneImage->image.getTextureReference().getWidth()
            << "x"
            << this->oneImage->image.getTextureReference().getHeight();
    return this->oneImage;
}

//--------------------------------------------------------------
vilainImage * vilainApp::addNewImageFromFile(ofFile file)
{
    return this->addNewImageFromFile(file.path());
}

//--------------------------------------------------------------
vilainImage * vilainApp::addNewImageFromFiles(vector<ofFile> list_of_files)
{
    for(ofFile file : list_of_files)
        this->oneImage = addNewImageFromFile(file);
    return oneImage;
}

