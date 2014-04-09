#include "vilainImage.h"

using namespace vilain;

vilainImage::vilainImage()
{
    vilainImage("groolot.jpg");
}

vilainImage::vilainImage(string path)
{
    LoadImage(path);
    ofAddListener(ofEvents().update, this, &vilainImage::update);
}

vilainImage::~vilainImage()
{
    ofRemoveListener(ofEvents().update, this, &vilainImage::update);
}

/** \brief Update method registered to the listeners manager ofAddListener
 *
 * \param e The ofEventArgs
 *
 */
void vilainImage::update(ofEventArgs &e)
{

}

void vilainImage::LoadImage(string path)
{
    image.loadImage(path);
}

void vilainImage::draw()
{
    image.getTextureReference().bind();
    of3dPrimitive::draw();
    image.getTextureReference().unbind();
    drawEditing();
}


