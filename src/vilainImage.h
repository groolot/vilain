#pragma once
#ifndef VILAINIMAGE_H
#define VILAINIMAGE_H

#include <libintl.h>
#define _(String) gettext(String)
#define _N(String) String

#include <ofMain.h>

#include "vilainObject.h"

namespace vilain
{
/** @brief Define an image contained in a rectangle

*/
class vilainImage : public vilainObject
{
public:
    /** Default constructor */
    vilainImage();
    /** Constructor with a path to an image file */
    vilainImage(string path);
    /** Default destructor */
    ~vilainImage();

    /** Load an image file into VImage#image attribute */
    void LoadImage(string path);

    void draw(void);
    void update(ofEventArgs &e);

    /** Image container to be used as texture (via the ofImage_#tex)
        or pixels map (via the ofImage_#pixels)
    */
    ofImage image;

protected:
private:
};
}
#endif // VILAINIMAGE_H
