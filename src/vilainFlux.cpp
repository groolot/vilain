#include "vilainFlux.h"

vilainFlux::vilainFlux()
{

}

vilainFlux::vilainFlux(int deviceID)
{
    flux.setDeviceID(deviceID);
}

vilainFlux::~vilainFlux()
{
    //dtor
}


void vilainFlux::init(int w, int h)
{
    sender.setup("localhost", 12345);
    flux.initGrabber(w,h);
    this->resizeToTexture(flux.getTextureReference());
}


void vilainFlux::update(void)
{
    flux.update();
}

void vilainFlux::draw(void)
{
    flux.getTextureReference().bind();
    of3dPrimitive::draw();
    flux.getTextureReference().unbind();
}

void vilainFlux::onPositionChanged(void)
{
    message.setAddress("/path/to/the/remote/parameter/to/control");
    message.addIntArg(getPosition().x);
    message.addIntArg(getPosition().y);
    sender.sendMessage(message);
    message.clear();
}
