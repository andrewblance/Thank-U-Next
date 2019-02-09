#ifndef __Game__
#define __Game__

#include "include/SDL2/SDL.h"
#include "include/SDL2/SDL_image.h"
#include <iostream>
#include <vector>
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "BetweenLevelState.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "AnimatedGraphic.h"

class Game
{
public:
    //set running variable to true
    bool init(const char* title, int xpos, int ypos, 
                int width, int height, bool fullscreen);

    void render();
    void update();
    void handleEvents();
    void clean();

    //function to access private running variable
    bool running() { return m_bRunning;}
    void quit() { m_bRunning = false; }

    //declare objects
    GameObject* m_go;
    GameObject* m_player;
    GameObject* m_enemy;

    //array to store gameobjects
    std::vector<GameObject*> m_gameObjects;

    //need to make a instance func to deal with sdl_renderer
    static Game* Instance()
    {
        if(s_pInstance ==0)
        {
            s_pInstance = new Game();
            return s_pInstance;
        }
        return s_pInstance;
    }

    SDL_Renderer* getRenderer() const {return m_pRenderer;}
    GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

    void setPlayerLives(int lives) { m_playerLives = lives; }
    int getPlayerLives() { return m_playerLives; }
    
    void setCurrentLevel(int currentLevel);
    const int getCurrentLevel() { return m_currentLevel; }

    void setNextLevel(int nextLevel) { m_nextLevel = nextLevel; }
    const int getNextLevel() { return m_nextLevel; }

    void setLevelComplete(bool levelComplete) { m_bLevelComplete = levelComplete; }
    const bool getLevelComplete() { return m_bLevelComplete; }

   int getGameWidth() const { return m_gameWidth; }
   int getGameHeight() const { return m_gameHeight; }
   float getScrollSpeed() { return m_scrollSpeed; }

   std::vector<std::string> getLevelFiles() { return m_levelFiles; }

private:
    Game();
    ~Game() {};

    //s_pInstance mem variable
    static Game* s_pInstance;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;

    int m_gameWidth;
    int m_gameHeight;
    float m_scrollSpeed;

    int m_playerLives;

    GameStateMachine* m_pGameStateMachine;

    int m_currentFrame;
    int m_currentLevel;
    int m_nextLevel;
    bool m_bLevelComplete;
    std::vector<std::string> m_levelFiles;

    bool m_bRunning;
};

typedef Game TheGame;

#endif /* defined(__Game__) */
