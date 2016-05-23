#include "vilainObject.h"

vilainObject::vilainObject(string nom, char key) :
    ofxOscRouterNode(nom),
    bDessinable(false),
    bAnimable(true),
    _activeKey(key)
{
    _alpha.reset(0);
    _alpha.setDuration(1);
    _alpha.setRepeatType(PLAY_ONCE);
    _alpha.setCurve(EASE_IN_EASE_OUT);
    initialiseOscMethodes();
}

vilainObject::~vilainObject()
{
}

void vilainObject::initialiseOscMethodes()
{
    addOscMethod("drawable");
    addOscMethod("animable");
    addOscMethod("alpha");
    addOscMethod("show");
    addOscMethod("hide");
    addOscMethod("duration");
}

void vilainObject::processOscCommand(const string& command, const ofxOscMessage& m)
{
    if(isMatch(command, "drawable"))
    {
        if(validateOscSignature("([TFif])", m))
        {
            Dessinable(getArgAsBoolUnchecked(m, 0));
        }
    }
    else if(isMatch(command, "animable"))
    {
        if(validateOscSignature("([TFif])", m))
        {
            Animable(getArgAsBoolUnchecked(m, 0));
        }
    }
    else if(isMatch(command, "show"))
    {
        if(validateOscSignature("([TFif][if]?[if]?)", m))
        {
            if(getArgAsBoolUnchecked(m, 0))
            {
                if(m.getNumArgs() >= 2)
                {
                    if(m.getNumArgs() == 3)
                    {
                        _alpha.setDuration(getArgAsFloatUnchecked(m, 2));
                    }

                    show(getArgAsFloatUnchecked(m, 1));
                }
                else
                {
                    show();
                }
            }
            else
            {
                if(m.getNumArgs() == 2)
                {
                    _alpha.setDuration(getArgAsFloatUnchecked(m, 1));
                }

                show();
            }
        }
    }
    else if(isMatch(command, "hide"))
    {
        if(validateOscSignature("([TFif])", m))
        {
            if(getArgAsBoolUnchecked(m, 0))
            {
                hide();
            }
        }
    }
    else if(isMatch(command, "alpha"))
    {
        if(validateOscSignature("([if])", m))
        {
            Alpha(getArgAsFloatUnchecked(m, 0));
        }
    }
    else if(isMatch(command, "duration"))
    {
        if(validateOscSignature("([if])", m))
        {
            _alpha.setDuration(getArgAsFloatUnchecked(m, 0));
        }
    }
}

void vilainObject::update(float dt)
{
    if(Animable())
    {
        _alpha.update(dt);
    }
}

void vilainObject::draw()
{
    if(Dessinable())
    {
        ofDrawBitmapString(ofxOscRouterNode::getFirstOscNodeAlias(), ofGetWidth() / 2, ofGetHeight() / 2);
    }
}

void vilainObject::show(float _maximumVisibility)
{
    _alpha.animateTo(_maximumVisibility);
}

void vilainObject::hide()
{
    _alpha.animateTo(0);
}
