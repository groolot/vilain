#include "vilainFlux.h"

vilainFlux::vilainFlux()
{
    //ctor
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
