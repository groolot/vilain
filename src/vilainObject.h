#ifndef VILAINOBJECT_H
#define VILAINOBJECT_H

#include <ofMain.h>
#include <ofxOsc.h>

class vilainObject : public ofPlanePrimitive
{
public:
    /** Default constructor */
    vilainObject();
    /** Default destructor */
    virtual ~vilainObject();

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
    ofxOscSender oscSender;
    ofxOscReceiver oscReceiver;
    ofxOscMessage oscOutMessage;
    string oscInputAddress;

    float nearestDistance = 0;
    ofVec2f nearestVertex;
    int nearestIndex = 0;
private:
    bool bEditMode = false;
};

#endif // VILAINOBJECT_H
