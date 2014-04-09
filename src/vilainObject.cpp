#include "vilainObject.h"

vilainObject::vilainObject()
{
    //ctor
}

vilainObject::~vilainObject()
{
    //dtor
}

void vilainObject::drawEditing()
{
    if(isEditing())
    {
        ofPushStyle();
        ofPushMatrix();
        ofTranslate(getPosition());
        ofVec2f mouse(ofGetMouseX()-getPosition().x, ofGetMouseY()-getPosition().y);
        unsigned int n = getMesh().getNumVertices();
        for(unsigned int i = 0; i < n; i++)
        {
            ofVec3f cur = getMesh().getVertex(i);
            float distance = cur.distance(mouse);
            if(i == 0 || distance < nearestDistance)
            {
                nearestDistance = distance;
                nearestVertex = cur;
                nearestIndex = i;
            }
        }
        getMesh().drawWireframe();
        ofSetColor(ofColor::red);
        ofLine(nearestVertex, mouse);
        ofFill();
        ofSetColor(ofColor::yellow);
        ofSetLineWidth(2.);
        ofCircle(nearestVertex, 4.);
        ofSetLineWidth(1.);
        ofDrawBitmapStringHighlight(ofToString(nearestIndex), mouse + ofVec2f(10., -10.));
        ofDrawAxis(30.);
        ofPopMatrix();
        ofPopStyle();
    }
}

void vilainObject::mouseDragged(int x, int y, int button)
{
    if(isEditing())
        getMeshPtr()->setVertex(nearestIndex, ofVec3f(x-getPosition().x, y-getPosition().y));
}
