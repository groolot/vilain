#include "vilainCore.h"

using namespace vilain;

//--------------------------------------------------------------
/// \brief Callback de construction de l'application
///
/// \return void
///
///
void vilainCore::setup()
{
#ifdef DEBUG
#endif // DEBUG
    ofSetFrameRate(60);
#ifdef TARGET_OPENGLES
    ofHideCursor();
#endif // TARGET_OPENGLES

    ofBackground(ofColor::black);
    /* OSC Configuration */
    oscSend.setup("localhost", 9876);
}

//--------------------------------------------------------------
/// \brief Callback de mise à jour des contenus (le cas échéant)
///
/// \return void
///
///
void vilainCore::update()
{
    ofxOscRouter::update();
}

//--------------------------------------------------------------
/// \brief Callback de dessin
///
/// \return void
///
///
void vilainCore::draw()
{
    if(!bBlackOut)
    {
        // Dessiner
    }
}

/// \brief Callback de sortie de programme (nettoyage au besoin)
///
/// \return void
///
///
void vilainCore::exit()
{
    ofGetWindowPtr()->setWindowShouldClose();
}

/// \brief Processeur de message OSC
///
///
///
/// \param command const string& La commande OSC
/// \param m const ofxOscMessage& La(es) valeur(s) associée(s) à la commande
/// \return void
///
///
void vilainCore::processOscCommand(const string& command, const ofxOscMessage& m)
{
    if(isMatch(command, "exit"))
    {
        if(validateOscSignature("([TFif])", m))
        {
            if(getArgAsBoolUnchecked(m, 0))
            {
                exit();
            }
        }
    }
    else if(isMatch(command, "debug"))
    {
        if(validateOscSignature("([TFif])", m))
        {
            bDebug = getArgAsBoolUnchecked(m, 0);
        }
    }
    else if(isMatch(command, "switchToScene"))
    {
        if(validateOscSignature("([i])", m))
        {
            // Switch to scene #
        }
    }
    else if(isMatch(command, "blackout"))
    {
        if(validateOscSignature("([TFif])", m))
        {
            bBlackOut = getArgAsBoolUnchecked(m, 0);
        }
    }
}

//--------------------------------------------------------------
/// \brief Callback de gestion du clavier pressé
///
/// \param key int La touche clavier pressée
/// \return void
///
///
void vilainCore::keyPressed(int key)
{
    if(key == OF_KEY_RETURN)
    {
    }
    else if(key == 'D')
    {
        m.clear();
        m.setAddress("/vilain/debug");
        m.addBoolArg(!bDebug);
        oscSend.sendMessage(m);
    }
    else if(key == ' ')
    {
        m.clear();
        m.setAddress("/vilain/blackout");
        m.addIntArg(!bBlackOut);
        oscSend.sendMessage(m);
    }
}

//--------------------------------------------------------------
/// \brief Callback de gestion du clavier relaché
///
/// \param key int La touche clavier relachée
/// \return void
///
///
void vilainCore::keyReleased(int key)
{
}

//--------------------------------------------------------------
/// \brief Callback de gestion du mouvement de la souris
///
/// \param x int Coordonnée X du pointeur
/// \param y int Coordonnée Y du pointeur
/// \return void
///
///
void vilainCore::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
/// \brief Callback de gestion de la pression des boutons de la souris
///
/// \param x int Coordonnée X du pointeur au moment de la pression
/// \param y int Coordonnée Y du pointeur au moment de la pression
/// \param button int Lequel des boutons est pressé
/// \return void
///
///
void vilainCore::mousePressed(int x, int y, int button)
{
    m.clear();
    m.setAddress("/vilain/blackout");
    m.addBoolArg(true);
    oscSend.sendMessage(m);
}

//--------------------------------------------------------------
/// \brief Callback de gestion de la relâche des boutons de la souris
///
/// \param x int Coordonnée X du pointeur au moment de la relâche
/// \param y int Coordonnée Y du pointeur au moment de la relâche
/// \param button int Lequel des boutons est relaché
/// \return void
///
///
void vilainCore::mouseReleased(int x, int y, int button)
{
    m.clear();
    m.setAddress("/vilain/blackout");
    m.addBoolArg(false);
    oscSend.sendMessage(m);
}

//--------------------------------------------------------------
/// \brief Callback de gestion du redimensionnement de la fenetre
///
/// \param w int Nouvelle largeur de la fenetre
/// \param h int Nouvelle hauteur de la fenetre
/// \return void
///
///
void vilainCore::windowResized(int w, int h)
{
}

