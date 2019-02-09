#include <iostream>
#include "BetweenLevelState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "StateParser.h"
#include "SoundManager.h"
#include "LevelParser.h"

const std::string BetweenLevelState::s_menuID = "CONT";

void BetweenLevelState::s_contToPlay()
{
   TheGame::Instance() -> getStateMachine() -> changeState(new PlayState()); 
}

void BetweenLevelState::s_exitFromCont()
{
   TheGame::Instance() -> quit(); 
}

void BetweenLevelState::s_contToMain()
{
   TheGame::Instance() -> setCurrentLevel(1);
   TheGame::Instance() -> getStateMachine() -> changeState(new MainMenuState());
}


void BetweenLevelState::update()
{
    pLevel -> update();
    for(int i=0; i<m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> update();
    }
}

void BetweenLevelState::render()
{
    pLevel -> render();
    for(int i=0; i<m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> draw();
    }
}

bool BetweenLevelState::onEnter()
{
    LevelParser levelParser;
    pLevel = levelParser.parseLevel("assets/continue.tmx");
    //parse the state
    StateParser stateParser;
    stateParser.parseState("test.xml", s_menuID, &m_gameObjects,
    &m_textureIDList);

    m_callbacks.push_back(0); //pushback 0 callback, start from 1
    m_callbacks.push_back(s_contToPlay);
    m_callbacks.push_back(s_exitFromCont);
    m_callbacks.push_back(s_contToMain);

    setCallbacks(m_callbacks);

    std::cout<< "enter cont state \n";
    return true;
}

bool BetweenLevelState::onExit()
{
    for(int i=0; i<m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> clean();
    }

    m_gameObjects.clear();

    for(int i = 0; i < m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance()->clearFromTextureMap(m_textureIDList[i]);
    }

    std::cout<< "exit mainmenustate \n";
    return true;
}

void BetweenLevelState::setCallbacks(const std::vector<Callback>&
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
