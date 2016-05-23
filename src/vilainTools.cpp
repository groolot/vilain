#include "vilainTools.h"

vilainTools * vilainTools::singleton = NULL;
ofStyle * vilainTools::styleStandard;

/// \brief vilainTools's singleton constructor
///
/// OSC Remote configuration and tooling singleton
///
vilainTools::vilainTools() :
    ofxOscRouterNode("tools")
{
    styleStandard = new ofStyle();
    styleStandard->bFill                 = false;
    styleStandard->lineWidth             = 1.0f;
    styleStandard->curveResolution       = 10;
    styleStandard->circleResolution      = 80;
    styleStandard->smoothing             = true;
    styleStandard->color.set(1, 1, 1, 1);
    styleStandard->bgColor.set(0);
    styleStandard->drawBitmapMode        = OF_BITMAPMODE_SIMPLE;
    addOscMethod("color");
    addOscMethod("curveResolution");
    addOscMethod("circleResolution");
}

/// \brief Singleton access
///
/// \return vilainTools* Singleton pointer
///
///
vilainTools * vilainTools::instance()
{
    if(!singleton)     // Only allow one instance of class to be generated.
    {
        singleton = new vilainTools();
    }

    return singleton;
}

/// \brief OSC filtering
///
/// \param command const string&
/// \param m const ofxOscMessage&
/// \return void
///
///
void vilainTools::processOscCommand(const string& command, const ofxOscMessage& m)
{
    if(isMatch(command, "lineWidth"))
    {
        if(validateOscSignature("([if])", m))
        {
            styleStandard->lineWidth = getArgAsFloatUnchecked(m, 0);
        }
    }
    else if(isMatch(command, "color"))
    {
        if(validateOscSignature("([f][f][f][f])", m))
        {
            styleStandard->color.set(getArgAsFloatUnchecked(m, 0),
                                     getArgAsFloatUnchecked(m, 1),
                                     getArgAsFloatUnchecked(m, 2),
                                     getArgAsFloatUnchecked(m, 3)
                                    );
        }
    }
    else if(isMatch(command, "curveResolution"))
    {
        if(validateOscSignature("([if])", m))
        {
            styleStandard->curveResolution = getArgAsIntUnchecked(m, 0);
        }
    }
    else if(isMatch(command, "circleResolution"))
    {
        if(validateOscSignature("([if])", m))
        {
            styleStandard->circleResolution = getArgAsIntUnchecked(m, 0);
        }
    }
}
