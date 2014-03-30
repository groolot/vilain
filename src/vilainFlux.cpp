#include "vilainFlux.h"

using namespace vilain;

vilainFlux::vilainFlux()
{

}

vilainFlux::vilainFlux(int deviceID)
{
    flux.setDeviceID(deviceID);
}

vilainFlux::~vilainFlux()
{
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
    flux.getTextureReference().bind();
    of3dPrimitive::draw();
    flux.getTextureReference().unbind();
}

void vilainFlux::onPositionChanged(void)
{
    oscOutMessage.setAddress("/path/to/the/remote/parameter/to/control");
    oscOutMessage.addIntArg(getPosition().x);
    oscOutMessage.addIntArg(getPosition().y);
    oscSender.sendMessage(oscOutMessage);
    oscOutMessage.clear();
}
