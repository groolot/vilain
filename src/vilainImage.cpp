#include "vilainImage.h"

vilainImage::vilainImage()
{
    vilainImage("groolot.jpg");
}

vilainImage::vilainImage(string path)
{
    LoadImage(path);
    ofAddListener(ofEvents().update, this, &vilainimage::update);
}

vilainImage::~vilainImage()
{
    ofRemoveListener(ofEvents().update, this, &vilainimage::update);
}

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
}
