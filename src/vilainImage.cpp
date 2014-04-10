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
#include "vilainImage.h"

using namespace vilain;

vilainImage::vilainImage()
{
    vilainImage("groolot.jpg");
}

vilainImage::vilainImage(string path)
{
    LoadImage(path);
    ofAddListener(ofEvents().update, this, &vilainImage::update);
}

vilainImage::~vilainImage()
{
    ofRemoveListener(ofEvents().update, this, &vilainImage::update);
}

/** \brief Update method registered to the listeners manager ofAddListener
 *
 * \param e The ofEventArgs
 *
 */
void vilainImage::update(ofEventArgs &e)
{

}

void vilainImage::LoadImage(string path)
{
    image.loadImage(path);
}

void vilainImage::draw()
{
    image.getTextureReference().bind();
    of3dPrimitive::draw();
    image.getTextureReference().unbind();
    drawEditing();
}


