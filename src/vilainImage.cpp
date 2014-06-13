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

/** \brief Simple constructor
 */
vilainImage::vilainImage()
{
    setKind(VILAIN_OBJECT_TYPE_IMAGE);
    setName("Image XXX");
}

/** \brief Constructor with a path to an image file
 * \param path string Path to an existing image file
 *
 */
vilainImage::vilainImage(string path)
{
    setKind(VILAIN_OBJECT_TYPE_IMAGE);
    setName(path);
    ofLogVerbose(PROG_NAME) << _("Construct a vilainImage object with this file: ") << path << endl;
    LoadImage(path);
    ofAddListener(ofEvents().update, this, &vilainImage::update);
}

vilainImage::~vilainImage()
{
    ofRemoveListener(ofEvents().update, this, &vilainImage::update);
}

/** \brief Update callback
 * \details This is called by the main program
 *
 * \param e ofEventArgs& The events are transmitted to help catching them here
 * \return void
 *
 */
void vilainImage::update(ofEventArgs &e)
{

}

/** \brief Load an image file into VImage#image attribute
 *
 * \param path string Path to an existing image file
 * \return void
 *
 */
void vilainImage::LoadImage(string path)
{
    ofLogVerbose(PROG_NAME) << _("Load image from file: ") << path << endl;
    image.loadImage(path);
    sName = path;
}

/** \brief Callback to perform the drawing
 *
 * This has to be called to draw the current object
 */
void vilainImage::draw()
{
    if(bDrawObject == true)
    {
        image.getTextureReference().bind();
        of3dPrimitive::draw();
        image.getTextureReference().unbind();
        drawEditing();
    }
}

void vilainImage::drawTypeObjectUI()
{

}
