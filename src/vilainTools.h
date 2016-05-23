#pragma once

#include <ofMain.h>
#include <ofxOscRouterNode.h>

class vilainTools : public ofxOscRouterNode
{
public:
    ~vilainTools() {};
    static vilainTools * instance();
    void processOscCommand(const string& command, const ofxOscMessage& m);
    static ofStyle * styleStandard;

private:
    vilainTools();
    static vilainTools * singleton;
};
