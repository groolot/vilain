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

}

/** \brief Constructor with a path to an image file
 * \author Gregory DAVID
 * \date 2014
 * \param path string Path to an existing image file
 *
 */
vilainImage::vilainImage(string path)
{
    LoadImage(path);
    ofAddListener(ofEvents().update, this, &vilainImage::update);
}

vilainImage::~vilainImage()
{
    ofRemoveListener(ofEvents().update, this, &vilainImage::update);
}

/** \brief Update callback
 * \details This is called by the main program
 * \author Gregory DAVID
 * \date 2014
 *
 * \param e ofEventArgs& The events are transmitted to help catching them here
 * \return void
 *
 */
void vilainImage::update(ofEventArgs &e)
{

}

/** \brief Load an image file into VImage#image attribute
 * \author Gregory DAVID
 * \date 2014
 *
 * \param path string Path to an existing image file
 * \return void
 *
 */
void vilainImage::LoadImage(string path)
{
    image.loadImage(path);
}

/** \brief Callback to perform the drawing
 *
 * This is called by the main program
 * \author Gregory DAVID
 * \date 2014
 */
void vilainImage::draw()
{
    image.getTextureReference().bind();
    of3dPrimitive::draw();
    image.getTextureReference().unbind();
    drawEditing();
}


