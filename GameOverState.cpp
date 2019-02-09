#include "GameOverState.h"
#include "MainMenuState.h"
#include "PlayState.h"
#include "TextureManager.h"
#include "AnimatedGraphic.h"
#include "Game.h"
#include "MenuButton.h"
#include "InputHandler.h"
#include "StateParser.h"
#include "LevelParser.h"

const std::string GameOverState::s_gameOverID = "GAMEOVER";

void GameOverState::s_gameOverToMain()
{
   TheGame::Instance() -> setCurrentLevel(1);
   TheGame::Instance() -> getStateMachine() -> changeState(new MainMenuState()); 
}

void GameOverState::s_restartPlay()
{
   TheGame::Instance() -> setCurrentLevel( TheGame::Instance() -> 
                          getCurrentLevel() - 1 );
   TheGame::Instance() -> getStateMachine() -> changeState(new PlayState()); 
}

void GameOverState::s_exitfromOver()
{
    TheGame::Instance() -> quit();
}

void GameOverState::update()
{
    pLevel -> update();
    for(int i=0; i<m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> update();
    }
}

void GameOverState::render()
{
    pLevel -> render();
    for(int i=0; i<m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> draw();
    }
}

bool GameOverState::onEnter()
{
    LevelParser levelParser;
    pLevel = levelParser.parseLevel("assets/gameoverstate.tmx");

    // parse the state
    StateParser stateParser;
    stateParser.parseState("test.xml", s_gameOverID, &m_gameObjects, 
    &m_textureIDList);
    
    m_callbacks.push_back(0);
    m_callbacks.push_back(s_gameOverToMain);
    m_callbacks.push_back(s_restartPlay);
    m_callbacks.push_back(s_exitfromOver);
    
    // set the callbacks for menu items
    setCallbacks(m_callbacks);
    
    std::cout << "entering GameOverState\n";
    return true;
}

bool GameOverState::onExit()
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

    std::cout<< "exit gameover \n";
    return true;
}

void GameOverState::setCallbacks(const std::vector<Callback>&
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

