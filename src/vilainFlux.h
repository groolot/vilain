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
#ifndef VILAINFLUX_H
#define VILAINFLUX_H

#include <libintl.h>
#define _(String) gettext(String)
#define _N(String) String

#include <ofMain.h>

#include "vilainObject.h"

namespace vilain
{
/** @brief Define a WebCam flow contained in a rectangle
*/
class vilainFlux : public vilainObject
{
public:
    vilainFlux();
    /** \brief Constructor with a device to be attached to
     *
     * \param deviceID int The device number
     * \see ofVideograbber
     */
    vilainFlux(int deviceID);
    virtual ~vilainFlux();

    /** \brief Act like a constructor, but callable
     *
     * \param w int Video grabber capture width
     * \param h int Video grabber capture height
     * \return void
     *
     */
    void init(int w, int h);

    /** \brief Update callback
     *
     * This is called by the main program
     *
     * \param e ofEventArgs& The events are transmitted to help catching them here
     * \return void
     *
     */
    void update(ofEventArgs &e);

    /** \brief Callback to perform the drawing
     *
     * This is called by the main program
     *
     * \param void
     * \return void
     *
     */
    void draw(void);

    virtual void onPositionChanged(void);

    ofVideoGrabber flux;
    int videoGrabberDeviceID;

protected:
private:
};
}
#endif // VILAINFLUX_H
