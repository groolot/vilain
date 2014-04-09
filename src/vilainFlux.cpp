#include "vilainFlux.h"

using namespace vilain;

vilainFlux::vilainFlux()
{
    flux.setDeviceID(videoGrabberDeviceID);
}

vilainFlux::vilainFlux(int deviceID) :
    videoGrabberDeviceID(deviceID)
{

}

vilainFlux::~vilainFlux()
{
    ofLogNotice(__PRETTY_FUNCTION__) << _("destructs vilainFlux deviceID: ") << videoGrabberDeviceID;
    flux.close();
    ofRemoveListener(ofEvents().update, this, &vilainFlux::update);
}

void vilainFlux::init(int w, int h)
{
    oscSender.setup("localhost", 12345);
    flux.initGrabber(w,h);
    resizeToTexture(flux.getTextureReference());
    ofAddListener(ofEvents().update, this, &vilainFlux::update);
}

void vilainFlux::update(ofEventArgs &e)
{
    flux.ofVideoGrabber::update();
}

void vilainFlux::draw(void)
{
	ofPushMatrix();
	ofTranslate(myPosition());
    flux.getTextureReference().bind();
    of3dPrimitive::draw();
    flux.getTextureReference().unbind();
    if(bEditMode)
    {
        ofVec2f mouse(ofGetMouseX()-myPosition().x, ofGetMouseY()-myPosition().y);
        unsigned int n = getMesh().getNumVertices();
        for(unsigned int i = 0; i < n; i++)
        {
            ofVec3f cur = getMesh().getVertex(i);
            float distance = cur.distance(mouse);
            if(i == 0 || distance < nearestDistance)
            {
                nearestDistance = distance;
                nearestVertex = cur;
                nearestIndex = i;
            }
        }
        getMesh().drawWireframe();
        ofSetColor(ofColor::gray);
        ofLine(nearestVertex, mouse);
        ofFill();
        ofSetColor(ofColor::yellow);
        ofSetLineWidth(2);
        ofCircle(nearestVertex, 4);
        ofSetLineWidth(1);
        ofDrawBitmapStringHighlight(ofToString(nearestIndex), mouse + ofVec2f(10, -10));
    }
    ofPopMatrix();
}

void vilainFlux::mouseDragged(int x, int y, int button)
{
	if(bEditMode)
		getMeshPtr()->setVertex(nearestIndex, ofVec3f(x-myPosition().x, y-myPosition().y));
}

void vilainFlux::myPosition(float px, float py, float pz)
{
	position = ofVec3f(px, py, pz);
}

void vilainFlux::onPositionChanged(void)
{
    oscOutMessage.setAddress("/path/to/the/remote/parameter/to/control");
    oscOutMessage.addIntArg(myPosition().x);
    oscOutMessage.addIntArg(myPosition().y);
    oscSender.sendMessage(oscOutMessage);
    oscOutMessage.clear();
}
