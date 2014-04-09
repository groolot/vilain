#pragma once
#ifndef VILAINFLUX_H
#define VILAINFLUX_H

#include <libintl.h>
#define _(String) gettext(String)
#define _N(String) String

#include <ofMain.h>
#include <ofxOsc.h>

namespace vilain
{
/** @brief Define a WebCam flow contained in a rectangle
*/
class vilainFlux : public ofPlanePrimitive
{
public:
    /** Default constructor */
    vilainFlux();
    /** Constructor with a device to attach to */
    vilainFlux(int deviceID);
    /** Default destructor */
    virtual ~vilainFlux();

    void init(int w, int h);
    void update(ofEventArgs &e);
    void draw(void);
    void mouseDragged(int x, int y, int button);

	ofVec3f myPosition(){return position;};
    void myPosition(float px, float py, float pz=0);

    virtual void onPositionChanged(void);

    ofVideoGrabber flux;
    int videoGrabberDeviceID;

    ofxOscSender oscSender;
    ofxOscReceiver oscReceiver;
    ofxOscMessage oscOutMessage;
    string oscInputAddress;

    bool bEditMode = true;
    float nearestDistance = 0;
    ofVec2f nearestVertex;
    int nearestIndex = 0;

protected:
private:
	ofVec3f position;
};
}
#endif // VILAINFLUX_H
