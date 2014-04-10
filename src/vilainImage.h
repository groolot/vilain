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
#ifndef VILAINIMAGE_H
#define VILAINIMAGE_H

#include <libintl.h>
#define _(String) gettext(String)
#define _N(String) String

#include <ofMain.h>

#include "vilainObject.h"

namespace vilain
{

/** \brief Image container with mesh modifier
 */
class vilainImage : public vilainObject
{
public:
    vilainImage();
    /** \brief Constructor with a path to an image file
     *
     * \param path string Path to an existing image file
     *
     */
    vilainImage(string path);
    virtual ~vilainImage();

    /** \brief Load an image file into VImage#image attribute
     *
     * \param path string Path to an existing image file
     * \return void
     *
     */
    void LoadImage(string path);

    /** \brief Callback to perform the drawing
     *
     * This is called by the main program
     *
     * \param void
     * \return void
     *
     */
    void draw(void);

    /** \brief Update callback
     *
     * This is called by the main program
     *
     * \param e ofEventArgs& The events are transmitted to help catching them here
     * \return void
     *
     */
    void update(ofEventArgs &e);

    /** Image container to be used as texture (via the ofImage_#tex)
        or pixels map (via the ofImage_#pixels)
    */
    ofImage image;

protected:
private:
};
}
#endif // VILAINIMAGE_H
