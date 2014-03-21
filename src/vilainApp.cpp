#include "vilainApp.h"

//--------------------------------------------------------------
void vilainApp::setup()
{
    vector<string> paths;
    paths.push_back("groolot.jpg");
    paths.push_back("groolot.png");

    vector<int> devicesID;
    devicesID.push_back(0);

    ofSetupScreen();
    ofSetFrameRate(30);
    ofLog() << "\tvilain::Mapping";
    ofDisableArbTex();

    addNewImageFromFiles(paths);

    for(auto deviceID : devicesID)
    {
        oneFlux = new vilainFlux(deviceID);
        oneFlux->init(160,120);
        fluxCollection.push_back(oneFlux);
    }
}

//--------------------------------------------------------------
void vilainApp::update()
{
    for(auto oneImage : imagesCollection)
        oneImage->setPosition(mouseX,mouseY,0);
    for(auto oneFlux : fluxCollection)
    {
        oneFlux->update();
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
    for(auto uneImage : imagesCollection)
        uneImage->draw();
    for(auto oneFlux : fluxCollection)
        oneFlux->draw();

    if(bInfoText)
    {
        stringstream ss;
        ss << "Framerate: " << ofToString(ofGetFrameRate(),0) << "\n";
        ss << "(t): Info Text"<<endl;
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
    oneImage = new vilainImage(path_to_file);
    oneImage->resizeToTexture(oneImage->image.getTextureReference());
    imagesCollection.push_back(oneImage);
    ofLogVerbose("vilainApp::addNewImageFromFile")
            << "Add file "
            << path_to_file
            << " as new vilainImage layer of size "
            << oneImage->image.getTextureReference().getWidth()
            << "x"
            << oneImage->image.getTextureReference().getHeight();
    return oneImage;
}

//--------------------------------------------------------------
vilainImage * vilainApp::addNewImageFromFiles(vector<string> paths_to_files)
{
    for(string path : paths_to_files)
        oneImage = addNewImageFromFile(path);
    return oneImage;
}

