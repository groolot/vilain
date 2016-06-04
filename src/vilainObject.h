#pragma once
#ifndef VILAINOBJECT_H
#define VILAINOBJECT_H

#include <ofMain.h>
#include <ofxOscRouterNode.h>
#include <ofxAnimatableFloat.h>

#include "vilain.h"

namespace vilain
{
class vilainObject :
    public ofxOscRouterNode
{
public:
    vilainObject(string nom, char key);
    virtual ~vilainObject();
    virtual void processOscCommand(const string& command, const ofxOscMessage& m);
    virtual void update(float);
    virtual void draw();
    virtual void show(float _maximumVisibility = 1);
    virtual void hide();

    void Alpha(float _valAlpha)
    {
        _alpha.reset(ofClamp(_valAlpha, 0, 1));
    };
    float Alpha()
    {
        return _alpha.val();
    };

    bool Drawable()
    {
        return bDrawable;
    };
    void Drawable(bool _val)
    {
        bDrawable = _val;
    };

    void Toggle()
    {
        bDrawable = !bDrawable;
    };

    void Animable(bool _val)
    {
        bAnimable = _val;
    };
    bool Animable()
    {
        return bAnimable;
    };

    const char Key()
    {
        return _activeKey;
    };
    void Key(char _key)
    {
        _activeKey = _key;
    };

protected:

private:
    virtual void initializeOscMethods();
    bool bDrawable;
    bool bAnimable;
    char _activeKey;
    ofxAnimatableFloat _alpha;
};
};
#endif
