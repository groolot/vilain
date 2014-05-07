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
#include "vilainObject.h"

using namespace vilain;

/** \brief Set correctly the object state as it is selected and edited or not
 *
 * \param _bEditmode The application editing mode state (hopefully)
 * \return void
 *
 */
void vilainObject::catchMe(bool _bEditMode)
{
    setSelected(true);
    setEditMode(_bEditMode);
}

/** \brief Set the object state as it is not selected nor in edit mode
 *
 * \post The object isn't selected nor editable anymore
 * \return void
 *
 */
void vilainObject::leaveMe()
{
    setSelected(false);
    setEditMode(false);
}

/** \brief Perform the drawing of all things inside the editing mode
 *
 * \pre To be drawn in editing mode, the object needs to be selected and set to edit mode
 * \return void
 *
 */
void vilainObject::drawEditing()
{
    if(isEditing() and isSelected())
    {
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(getPosition());
        ofVec2f mouse(ofGetMouseX()-getX(), ofGetMouseY()-getY());
        unsigned int n = getMesh().getNumVertices();
        for(unsigned int i = 0; i < n; i++)
        {
            ofVec3f cur = getMesh().getVertex(i);
            float distance = cur.distance(mouse);
            if(i == 0 || distance < nearestMouseDistanceToMeshVertex)
            {
                nearestMouseDistanceToMeshVertex = distance;
                nearestMeshVertex = cur;
                nearestMeshVertexIndex = i;
            }
        }
        getMesh().drawWireframe();
        ofSetColor(ofColor::red);
        ofLine(nearestMeshVertex, mouse);
        ofFill();
        ofSetColor(ofColor::yellow);
        ofSetLineWidth(2.);
        ofCircle(nearestMeshVertex, 4.);
        ofSetLineWidth(1.);
        ofDrawBitmapStringHighlight(ofToString(nearestMeshVertexIndex), mouse + ofVec2f(10., -10.));
        ofDrawAxis(30.);
        ofPopMatrix();
        ofPopStyle();
    }
}

/** \brief Control what to do when the mouse is dragged
 *
 * \param[in] x,y int Mouse 2D position in screen coordinates
 * \param button int Pushed button value
 * \return void
 *
 */
void vilainObject::mouseDragged(int x, int y, int button)
{
    if(isEditing())
    {
        if(button == OF_MOUSE_BUTTON_LEFT)
        {
            getMeshPtr()->setVertex(nearestMeshVertexIndex, ofVec3f(x-getX(), y-getY()));
        }
        else if(button == OF_MOUSE_BUTTON_MIDDLE)
        {
            mouseDistance = ofVec2f(x, y) - mousePressedPosition;
            ofVec2f futurPosition = objectPressedPosition + mouseDistance;
            setPosition(futurPosition.x, futurPosition.y, getZ());
        }
    }
    mouseButton = button;
}

/** \brief Control what to do when the mouse is pressed
 *
 * \param[in] x,y int Mouse 2D position in screen coordinates
 * \param button int Pushed button value
 * \return void
 *
 */
void vilainObject::mousePressed(int x, int y, int button)
{
    mousePressedPosition = ofVec2f(x,y);
    objectPressedPosition = ofVec2f(getX(), getY());
    mouseButton = button;
}

/** \brief Control what to do when the mouse is released
 *
 * \param[in] x,y int Mouse 2D position in screen coordinates
 * \param button int Pushed button value
 * \return void
 *
 */
void vilainObject::mouseReleased(int x, int y, int button)
{
    mouseReleasedPosition = ofVec2f(x,y);
    mouseButton = button;
}

void vilainObject::keyPressed(int key)
{
    if(isEditing())
    {
        if(key=='1')
        {
            setResolution(2., 2.);
        }
        else if(key=='2')
        {
            setResolution(3., 3.);
        }
        else if(key=='3')
        {
            setResolution(4., 4.);
        }
        else if(key==OF_KEY_UP)
        {
            if(getZ()<std::numeric_limits<int>::max()-1)
                move(0,0,1);
        }
        else if(key==OF_KEY_DOWN)
        {
            if(getZ()>=1)
                move(0,0,-1);
        }
    }
    else
    {

    }
}
