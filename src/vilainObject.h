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
    vilainObject() {resolution = ofVec2f(3,2);};
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
    void drawEditing();
    void mouseDragged(int x, int y, int button);

protected:
    ofxOscSender oscSender;/**< \brief Used to intitiate an OSC client for UDP message sending */
    ofxOscMessage oscOutMessage;/**< \brief The OSC output message container */
    ofxOscReceiver oscReceiver;/**< \brief Used to create an OSC server listening for UDP messages */
    string oscInputAddress;/**< \brief Specify the OSC address to listen to */

    float nearestMouseDistanceToMeshVertex = 0;/**< \brief Keep the distance from mouse to nearest object mesh vertex */
    ofVec2f nearestMeshVertex;/**< \brief Keep coordinates of the mouse nearest object mesh vertex */
    int nearestMeshVertexIndex = 0;/**< \brief Keep index of the mouse nearest object mesh vertex */
private:
    bool bEditMode = false;/**< \brief Toggle variable for editing mode \li \c true for editing, \li \c false for performance mode */
};
}

#endif // VILAINOBJECT_H
