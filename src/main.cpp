#include <ofMain.h>

#include "vilain.h"
#include "vilainCore.h"

using namespace vilain;

//========================================================================
int main()
{
    setlocale(LC_ALL, "");
    bindtextdomain(PROG_NAME, ".");
    textdomain(PROG_NAME);
    ofSetLogLevel(PROG_NAME, OF_LOG_VERBOSE);
    ofSetLogLevel(OF_LOG_WARNING);

    ofSetupOpenGL(1024, 768, OF_WINDOW);
    ofRunApp(new vilainCore());
    return 0;
}
