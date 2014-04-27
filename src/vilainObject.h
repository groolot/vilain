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

#include <ofMain.h>
#include <ofxOsc.h>

#include "vilain.h"

namespace vilain
{
/** \brief Pseudo object with mesh modifier
 * \details A vilainObject agregate all the needs for sub-objects like vilainImage, vilainFlux, etc.
 * \author Gregory DAVID
 * \date 2014
 */
class vilainObject : public ofPlanePrimitive
{
public:
    vilainObject() : ofPlanePrimitive(1, 1, 2, 2) {};
    vilainObject(float w, float h, int columns, int rows) : ofPlanePrimitive(w,h,columns,rows) {};
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

    /** \brief Does it selected?
     *
     * \return bool \c true if selected, \c false if not
     *
     */
    bool isSelected()
    {
        return bSelected;
    }

    /** \brief Change the selected state
     *
     * \param state bool The selected state to be set
     * \return bool \c true if selected, \c false if not
     *
     */
    bool setSelected(bool state)
    {
        bSelected = state;
        return bSelected;
    }

    void catchMe(bool _bEditMode);
    void leaveMe();
    virtual void draw() {};
    void drawEditing();
    void mouseDragged(int x, int y, int button);

protected:
    ofxOscSender oscSender;/**< \brief Used to initiate an OSC client for UDP message sending */
    ofxOscMessage oscOutMessage;/**< \brief The OSC output message container */
    ofxOscReceiver oscReceiver;/**< \brief Used to create an OSC server listening for UDP messages */
    string oscInputAddress;/**< \brief Specify the OSC address to listen to */

    float nearestMouseDistanceToMeshVertex = 0;/**< \brief Keep the distance from mouse to nearest object mesh vertex */
    ofVec2f nearestMeshVertex;/**< \brief Keep coordinates of the mouse nearest object mesh vertex */
    int nearestMeshVertexIndex = 0;/**< \brief Keep index of the mouse nearest object mesh vertex */

private:
    bool bEditMode = false;/**< \brief Per object edit mode flag \li \c true for editing, \li \c false (default) for performance mode */
    bool bSelected = false; /**< \brief Is selected or not? */
    int mouseButton;
};
}

#endif // VILAINOBJECT_H
