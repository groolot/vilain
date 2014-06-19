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
#include "vilainApp.h"

using namespace vilain;

/** \brief Constructor creating a 2x2 rectangle plane primitive mesh
 */
vilainObject::vilainObject() :
    ofPlanePrimitive(1, 1, 2, 2)
{
}

/** \brief Parametric constructor
 *
 * \param w float Width of plane
 * \param h float Height of plane
 * \param columns int X mesh resolution
 * \param rows int Y mesh resolution
 *
 */
vilainObject::vilainObject(float w, float h, int columns, int rows) :
    ofPlanePrimitive(w, h, columns, rows)
{
}

/** \brief Compare operator while sorting with std::sort algorithm
 *
 * \param otherObject vilainObject The right hand operand
 * \return bool
 *
 */
bool vilainObject::operator()(ofPtr<vilainObject> left, ofPtr<vilainObject> right)
{
    return left->getZ() > right->getZ();
}

/** \brief Give the editing mode status
 *
 * \return bool The editing mode : true or false
 *
 */
bool vilainObject::isEditing()
{
    return bEditMode;
}

/** \brief Change the editing mode
 *
 * \param mode bool The editing mode to be set
 * \return bool The new editing mode
 *
 */
bool vilainObject::setEditingMode(bool mode)
{
    bEditMode = mode;
    return bEditMode;
}

/** \brief Does it selected?
 *
 * \return bool \c true if selected, \c false if not
 *
 */
bool vilainObject::isSelected()
{
    return bSelected;
}

/** \brief Change the selected state
 *
 * \param state bool The selected state to be set
 * \return bool \c true if selected, \c false if not
 *
 */
bool vilainObject::setSelected(bool state)
{
    bSelected = state;
    return bSelected;
}

/** \brief Set correctly the object state as it is selected and edited or not
 *
 * \param _bEditmode The application editing mode state (hopefully)
 * \return void
 *
 */
void vilainObject::catchMe(bool _bEditMode)
{
    setSelected(true);
    setEditingMode(_bEditMode);
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
    setEditingMode(false);
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
        ofVec2f mouse(ofGetMouseX() - getX(), ofGetMouseY() - getY());
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

        glDepthFunc(GL_ALWAYS);
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
        glDepthFunc(GL_LESS);
        ofPopMatrix();
        ofPopStyle();
    }
}

//--------------------------------------------------------------
/** \brief Setup the parent name of objects
 *
 * \return void
 *
 */
void vilainObject::setParentName()
{
    allParentName.clear();

    for(ofPtr<vilainObject> parent : vilainApp::allObjects)
    {
        if(parent->parentName != objectName && parent->objectName != objectName)
        {
            allParentName.push_back(parent->objectName);
        }
    }
}

//--------------------------------------------------------------
/** \brief Setup the children name of objects
 *
 * \return void
 *
 */
void vilainObject::setChildrenNames()
{
    allChildrenNames.clear();

    for(ofPtr<vilainObject> child : vilainApp::allObjects)
    {
        if(child->parentName == objectName)
        {
            allChildrenNames.push_back(child->objectName);
        }
    }
}

//--------------------------------------------------------------
/** \brief Draw per object UI
 *
 * \return void
 *
 */
void vilainObject::drawObjectUI()
{
    setParentName();
    setChildrenNames();

    objectUI = new ofxUIScrollableCanvas(373, 0, 300, ofGetHeight() - 10);

    ofAddListener(objectUI->newGUIEvent, this, &vilainObject::ObjectUI_Event); /** Listener for wait event */

    bObjectUI_Visible = true;
    bObjectUI_Drawed = true;

    objectUI->setName(objectName);
    objectUI->addLabel(objectName);
    objectUI->addSpacer();
    objectUI->addToggle("Show object", bDrawObject); /** Hide/Show toggle */
    objectUI->addSpacer();

    /** Position sliders */
    xPositionSlider = objectUI->addSlider("Position x", 0 - getWidth() / 2, ofGetWindowWidth() + getWidth() / 2, getX());
    yPositionSlider = objectUI->addSlider("Position y", 0 - getHeight() / 2, ofGetWindowHeight() + getHeight() / 2, getY());
    objectUI->addSpacer();


    /** Color sliders */
    objectUI->addSlider("Red", 0, 1, &color.r);
    objectUI->addSlider("Green", 0, 1, &color.g);
    objectUI->addSlider("Blue", 0, 1, &color.b);
    objectUI->addSlider("Alpha", 0, 1, &color.a);

    objectUI->addSpacer();
    drawTypeObjectUI();
    objectUI->addSpacer();
    ddl = objectUI->addDropDownList("Parent list", allParentName); /** List of parent */
    ddl->setAllowMultiple(false); /** Disable multiple select */
    ddl->setAutoClose(true); /** enable auto close */
    objectUI->addSpacer();

    for(string child : allChildrenNames)
    {
        objectUI->addLabel(child, OFX_UI_FONT_SMALL);
    }
}

//--------------------------------------------------------------
/** \brief Wait per object UI event
 *
 * \return void
 *
 */
void vilainObject::ObjectUI_Event(ofxUIEventArgs& e)
{
    string eventName = e.getName();

    if(eventName == "Show object") /** Hide/Show oject */
    {
        ofxUIToggle *toggleShowObject = (ofxUIToggle *) e.widget;
        bDrawObject = toggleShowObject->getValue(); /** Draw/Hide object */
    }

    if(eventName == "Position x") /** Position x changed */
    {
        ofxUISlider *xSliderPosition = (ofxUISlider *) e.widget;
        setPosition(xSliderPosition->getValue(), getY(), getZ()); /** Positioning */
    }

    if(eventName == "Position y") /** Position y changed */
    {
        ofxUISlider *ySliderPosition = (ofxUISlider *) e.widget;
        setPosition(getX(), ySliderPosition->getValue(), getZ()); /** Positioning */
    }

    if(eventName == "Parent list") /** Parent change */
    {
        if(ddl->getSelectedNames().size() != 0)
        {
            parentName = ddl->getSelectedNames()[0];

            for(ofPtr<vilainObject> parentObject : vilainApp::allObjects)
            {
                if(parentObject->objectName == parentName)
                {
                    setParent(*parentObject); /** Set parent */

                    /** Redefine position */
                    xPositionSlider->setMaxAndMin(parentObject->getWidth() / 2 + getWidth() / 2, -parentObject->getWidth() / 2 - getWidth() / 2);
                    yPositionSlider->setMaxAndMin(parentObject->getHeight() / 2 + getHeight() / 2, -parentObject->getHeight() / 2 - getHeight() / 2);
                    setPosition(0, 0, 0);
                }
            }
        }
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
            getMeshPtr()->setVertex(nearestMeshVertexIndex, ofVec3f(x - getX(), y - getY()));
        }
        else if(button == OF_MOUSE_BUTTON_MIDDLE)
        {
            mouseDistance = ofVec2f(x, y) - mousePressedPosition;
            ofVec2f futurPosition = objectPressedPosition + mouseDistance;
            setPosition(futurPosition.x, futurPosition.y, getZ());

            if(bObjectUI_Visible == true)
            {
                xPositionSlider->setValue(futurPosition.x);
                yPositionSlider->setValue(futurPosition.y);
            }
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
    mousePressedPosition = ofVec2f(x, y);
    objectPressedPosition = ofVec2f(getX(), getY());
    mouseButton = button;

    if(isEditing())
    {
        if(mouseButton == OF_MOUSE_BUTTON_5)
        {
            sendOneStepToBackground();
        }
        else if(mouseButton == OF_MOUSE_BUTTON_6)
        {
            sendOneStepToForeground();
        }
    }
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
    mouseReleasedPosition = ofVec2f(x, y);
    mouseButton = button;
}

/** \brief Control what to do when a key is pressed
 *
 * \param[in] key int Keyboard key value
 * \return void
 *
 */
void vilainObject::keyPressed(int key)
{
    if(isEditing())
    {
        if(key == '1')
        {
            setResolution(2., 2.);
        }
        else if(key == '2')
        {
            setResolution(3., 3.);
        }
        else if(key == '3')
        {
            setResolution(4., 4.);
        }
        else if(key == OF_KEY_DOWN)
        {
            sendOneStepToBackground();
        }
        else if(key == OF_KEY_UP)
        {
            sendOneStepToForeground();
        }
    }
    else
    {

    }
}

/** \brief Send object one step under
 *
 * \return void
 *
 */
void vilainObject::sendOneStepToBackground()
{
    if(getZ() >= 1)
    {
        move(0, 0, -1);
    }
}

/** \brief Send object one step upper
 *
 * \return void
 *
 */
void vilainObject::sendOneStepToForeground()
{
    if(getZ() < std::numeric_limits<int>::max() - 1)
    {
        move(0, 0, 1);
    }
}

/** \brief Set Kind variable
 *
 * \param _kind vilainObjectType
 * \return void
 *
 */
void vilainObject::setKind(vilainObjectType _kind)
{
    Kind = _kind;
}

/** \brief Get kind of object
 *
 * \return vilainObjectType
 *
 */
vilainObjectType vilainObject::getKind()
{
    return Kind;
}
