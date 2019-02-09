#include <iostream>
#include "MainMenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "StateParser.h"
#include "SoundManager.h"
#include "LevelParser.h"

const std::string MainMenuState::s_menuID = "MENU";

void MainMenuState::s_menuToPlay()
{
   //TheSoundManager::Instance()->playSound("boom", 0);
   TheGame::Instance() -> getStateMachine() -> changeState(new PlayState()); 
}

void MainMenuState::s_exitFromMenu()
{
   TheGame::Instance() -> quit(); 
}

void MainMenuState::update()
{
    pLevel -> update();
    for(int i=0; i<m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> update();
    } 
}

void MainMenuState::render()
{
    pLevel -> render();
    for(int i=0; i<m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> draw();
    } 
}

bool MainMenuState::onEnter()
{
    LevelParser levelParser;
    pLevel = levelParser.parseLevel("assets/mainmenu.tmx");

    //parse the state
    StateParser stateParser;
    stateParser.parseState("test.xml", s_menuID, &m_gameObjects,
    &m_textureIDList);   
    
    std::cout<< m_gameObjects.size() << "\n";

    m_callbacks.push_back(0); //pushback 0 callback, start from 1
    m_callbacks.push_back(s_menuToPlay);
    m_callbacks.push_back(s_exitFromMenu);

    setCallbacks(m_callbacks);

    std::cout<< "enter main menu state \n";
    return true;
}

bool MainMenuState::onExit()
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

void MainMenuState::setCallbacks(const std::vector<Callback>&
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
