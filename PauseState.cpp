#include "MenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "PauseState.h"
#include "MenuButton.h"
#include "StateParser.h"
#include "LevelParser.h"

const std::string PauseState::s_pauseID = "PAUSE";

void PauseState::s_pauseToMain()
{
   TheGame::Instance() -> setCurrentLevel(1);
   TheGame::Instance() -> getStateMachine() -> changeState(new MainMenuState()); 
}

void PauseState::s_resumePlay()
{
   TheGame::Instance() -> getStateMachine() -> popState(); 
}


void PauseState::update()
{
    pLevel -> update();
    for(int i=0; i<m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> update();
    }
}

void PauseState::render()
{
    pLevel -> render();
    for(int i=0; i<m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> draw();
    }
}

bool PauseState::onEnter()
{
    LevelParser levelParser;
    pLevel = levelParser.parseLevel("assets/pausestate.tmx");

    StateParser stateParser;
    stateParser.parseState("test.xml", s_pauseID, &m_gameObjects,
    &m_textureIDList);

    m_callbacks.push_back(0);
    m_callbacks.push_back(s_pauseToMain);
    m_callbacks.push_back(s_resumePlay);
    
    setCallbacks(m_callbacks);

    std::cout<< "enter pause state \n";
    return true;
}

bool PauseState::onExit()
{
    for(int i=0; i<m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> clean();
    }
    m_gameObjects.clear();

    for(int i=0; i<m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance() -> clearFromTextureMap(m_textureIDList[i]);
    }

    TheInputHandler::Instance() -> reset();

    std::cout<< "exit pause state \n";
    return true;
}

void PauseState::setCallbacks(const std::vector<Callback>&
callbacks)
{
    //go through game objects
    for(int i = 0; i < m_gameObjects.size(); i++)
    {
        //if they are of menubutton then assign a callback
        //based on id passed from xml
        if(dynamic_cast<MenuButton*>(m_gameObjects[i]))
        {
            MenuButton* pButton=
            dynamic_cast<MenuButton*>(m_gameObjects[i]);
            pButton -> setCallback(callbacks[pButton-> getCallbackID()]);
        }
    }
}
