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
    flux.getTextureReference().bind();
    of3dPrimitive::draw();
    flux.getTextureReference().unbind();
	drawEditing();
}

void vilainFlux::onPositionChanged(void)
{
    oscOutMessage.setAddress("/path/to/the/remote/parameter/to/control");
    oscOutMessage.addIntArg(getPosition().x);
    oscOutMessage.addIntArg(getPosition().y);
    oscSender.sendMessage(oscOutMessage);
    oscOutMessage.clear();
}
