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

#include <ofMain.h>

#include "vilain.h"
#include "vilainObject.h"

namespace vilain
{
/** \brief Image container with mesh modifier
 * \author Gregory DAVID
 * \date 2014
 */
class vilainImage : public vilainObject
{
public:
    vilainImage();
    vilainImage(string path);
    virtual ~vilainImage();

    void LoadImage(string path);
    void draw(void);
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
