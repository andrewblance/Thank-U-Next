#include <iostream>
#include "PlayState.h"
#include "GameOverState.h"
#include "PauseState.h"
#include "Game.h"
#include "InputHandler.h"
#include "LevelParser.h"
#include "Level.h"
#include "TextureManager.h"
#include "StateParser.h"

const std::string PlayState::s_playID = "PLAY";

void PlayState::update()
{ 
    if(TheInputHandler::Instance() -> isKeyDown(SDL_SCANCODE_ESCAPE))
    {
        TheGame::Instance() -> getStateMachine() -> 
        pushState(new PauseState());
    } 
    if(TheGame::Instance()->getPlayerLives() == 0)
    {
        TheGame::Instance()->getStateMachine()->changeState(new GameOverState());
    }
    pLevel -> update();
} 

void PlayState::render()
{ 
    pLevel -> render();

    int currentFrame;
    currentFrame = TheGame::Instance() -> getPlayerLives();

    TheTextureManager::Instance()->drawFrame("lives", 
            100, 100, 10, 30, 0, currentFrame, 
            TheGame::Instance()->getRenderer(), 0.0, 255);
}

bool PlayState::onEnter()
{
    TheGame::Instance()->setPlayerLives(3);
    //parse the state :) 

    LevelParser levelParser; 
    pLevel = levelParser.parseLevel(TheGame::Instance() -> 
                getLevelFiles()[TheGame::Instance()->getCurrentLevel() - 1].c_str());
    
    std::cout<< "enter playstate \n";
    return true;
}

bool PlayState::onExit()
{
    for(int i=0; i<m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> clean();
    }
    m_gameObjects.clear();

    for(int i = 0; i<m_textureIDList.size(); i++)
    {
        TheTextureManager::Instance() -> 
        clearFromTextureMap(m_textureIDList[i]);
    }
    
    TheInputHandler::Instance()->reset();
    std::cout<< "exit playstate \n";
    return true; 
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = p1 -> getPosition().getX();
    rightA = p1 -> getPosition().getX() + p1-> getWidth();
    topA = p1 -> getPosition().getY();
    bottomA = p1 -> getPosition().getY() + p1->getHeight();

    leftB = p2 -> getPosition().getX();
    rightB = p2 -> getPosition().getX() + p2-> getWidth();
    topB = p2 -> getPosition().getY();
    bottomB = p2 -> getPosition().getY() + p2->getHeight();

    if(bottomA <= topB){return false;}
    if(topA >= bottomB){return false;}
    if(rightA <= leftB){return false;}
    if(leftA >= rightB){return false;}

    return true;
} 
