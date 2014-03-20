#include "vilainImage.h"

vilainImage::vilainImage()
{

}

vilainImage::vilainImage(string path)
{
    LoadImage(path);
}

vilainImage::~vilainImage()
{
    //dtor
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
