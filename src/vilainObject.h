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
#ifndef VILAINOBJECT_H
#define VILAINOBJECT_H

#include <libintl.h>
#define _(String) gettext(String)
#define _N(String) String

#include <ofMain.h>
#include <ofxOsc.h>

namespace vilain
{
/** \brief Pseudo object with mesh modifier
 *
 * A vilainObject agregate all the needs for sub-objects like vilainImage, vilainFlux, etc.
 */
class vilainObject : public ofPlanePrimitive
{
public:
    vilainObject() {};
    virtual ~vilainObject() {};

    /** \brief Give the editing mode status
     *
     * \return bool The editing mode : true or false
     *
     */
    bool isEditing()
    {
        return bEditMode;
    };

    /** \brief Change the editing mode
     *
     * \param mode bool The editing mode to be set
     * \return bool The new editing mode
     *
     */
    bool setEditMode(bool mode)
    {
        bEditMode = mode;
        return bEditMode;
    };

    /** \brief Perform the drawing of all things inside the editing mode
     *
     * \return void
     *
     */
    void drawEditing();

    /** \brief Control what to do when the mouse is dragged
     *
     * \param x int
     * \param y int
     * \param button int
     * \return void
     *
     */
    void mouseDragged(int x, int y, int button);

protected:
    ofxOscSender oscSender;/**< Variable used to intitiate OSC  message sending */
    ofxOscReceiver oscReceiver;
    ofxOscMessage oscOutMessage;
    string oscInputAddress;

    float nearestDistance = 0;
    ofVec2f nearestVertex;
    int nearestIndex = 0;
private:
    bool bEditMode = false;
};
}

#endif // VILAINOBJECT_H
