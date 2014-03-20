#ifndef VILAINFLUX_H
#define VILAINFLUX_H

#include <ofMain.h>

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
    void update(void);
    void draw(void);

    ofVideoGrabber flux;
protected:
private:
};

#endif // VILAINFLUX_H
