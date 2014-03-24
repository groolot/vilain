#include "vilainFlux.h"

vilainFlux::vilainFlux()
{

}

vilainFlux::vilainFlux(int deviceID)
{
    this->flux.setDeviceID(deviceID);
}

vilainFlux::~vilainFlux()
{
    ofRemoveListener(ofEvents().update, this, &vilainFlux::update);
}

void vilainFlux::init(int w, int h)
{
    this->oscSender.setup("localhost", 12345);
    this->flux.initGrabber(w,h);
    this->resizeToTexture(this->flux.getTextureReference());
    ofAddListener(ofEvents().update, this, &vilainFlux::update);
}

void vilainFlux::update(ofEventArgs &e)
{
    this->flux.ofVideoGrabber::update();
}

void vilainFlux::draw(void)
{
    this->flux.getTextureReference().bind();
    of3dPrimitive::draw();
    this->flux.getTextureReference().unbind();
}

void vilainFlux::onPositionChanged(void)
{
    this->oscOutMessage.setAddress("/path/to/the/remote/parameter/to/control");
    this->oscOutMessage.addIntArg(getPosition().x);
    this->oscOutMessage.addIntArg(getPosition().y);
    this->oscSender.sendMessage(oscOutMessage);
    this->oscOutMessage.clear();
}
