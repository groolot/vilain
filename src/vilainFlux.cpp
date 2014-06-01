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
}

/** \brief Constructor with a device to be attached to
 *
 * \param deviceID int The device number
 * \see ofVideograbber
 */
vilainFlux::vilainFlux(int deviceID, int w, int h) : vilainObject(w, h, 2, 2),
    videoGrabberDeviceID(deviceID)
{
    flux.initGrabber(w, h);
    resizeToTexture(flux.getTextureReference());
    ofAddListener(ofEvents().update, this, &vilainFlux::update);
}

vilainFlux::~vilainFlux()
{
    ofLogVerbose(PROG_NAME) << _("Destructs vilainFlux deviceID: ") << videoGrabberDeviceID;
    flux.close();
    ofRemoveListener(ofEvents().update, this, &vilainFlux::update);
}

/** \brief Update callback
 *
 * This is called by the main program
 *
 * \param e ofEventArgs& The events are transmitted to help catching them here
 * \return void
 *
 */
void vilainFlux::update(ofEventArgs &e)
{
    flux.ofVideoGrabber::update();
}

/** \brief Callback to perform the drawing
 *
 * This is called by the main program
 *
 * \param void
 * \return void
 *
 */
void vilainFlux::draw(void)
{
    flux.getTextureReference().bind();
    of3dPrimitive::draw();
    flux.getTextureReference().unbind();
    drawEditing();
}

/** \brief Object position changing CallBack
 *
 * \param void
 * \return virtual void
 *
 */
void vilainFlux::onPositionChanged(void)
{

}
