#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "eye.h"
#include "InputHandler.h"
#include "SoundManager.h"
#include "ScrollingBackground.h"

Game* Game::s_pInstance = 0;

Game::Game():
m_pWindow(0),
m_pRenderer(0),
m_bRunning(false),
m_pGameStateMachine(0),
m_playerLives(3),
m_scrollSpeed(0.8),
m_bLevelComplete(false)
{
    m_levelFiles.push_back("assets/map1.tmx");
    m_levelFiles.push_back("assets/map2.tmx");
    m_currentLevel = 1;
}

bool Game::init(const char* title, int xpos, int ypos,
int width, int height, bool fullscreen)
{
	int flags = 0;

    m_gameWidth = width;
    m_gameHeight = height;

    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) ==0)
    {
        std::cout << "sdl init success\n";
        //if success
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        //make renderer
        if (m_pWindow != 0)
        {
            std::cout<<"window creation success!!\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            
            if(m_pRenderer != 0) //renderer success
            {
                std::cout << "renderer successful!\n";
                SDL_SetRenderDrawColor(m_pRenderer, 200, 0, 0, 200);
            }
            else
            {
                std::cout<<"render init fail\n";
                return false;
            }
        }
        else
        {
            std::cout<<"window init fail\n";
            return false;
        }
    }
    else
    {
        std::cout<<"sdl init fail\n";
        return false;
    }
    
    std::cout <<"init success\n";

    TheSoundManager::Instance() -> load("assets/song.wav", 
                                                "music1", SOUND_MUSIC);
    TheSoundManager::Instance() -> load("assets/boom.wav", "boom", SOUND_SFX);

    TheSoundManager::Instance() -> playMusic("music1", -1);

    TheTextureManager::Instance() -> load("assets/lives.png", "lives", m_pRenderer);

    TheGameObjectFactory::Instance() -> registerType("MenuButton", 
    new MenuButtonCreator());
    TheGameObjectFactory::Instance() -> registerType("Player", 
    new PlayerCreator());
    TheGameObjectFactory::Instance() -> registerType("Eye", 
    new EyeCreator());
    TheGameObjectFactory::Instance() -> registerType("AnimatedGraphic", 
    new AnimatedGraphicCreator());
    TheGameObjectFactory::Instance()->registerType("ScrollingBackground", 
    new ScrollingBackgroundCreator());

    //initialise joysticks
    TheInputHandler::Instance() -> initialiseJoysticks();
    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MainMenuState());
    m_bRunning = true;
    return true;
}

void Game::render()
{
    //clear the renderer to draw color
    SDL_RenderClear(m_pRenderer);
    //loop through objects in array and draw!
    m_pGameStateMachine -> render();
    //draw to the screen
    SDL_RenderPresent(m_pRenderer);
}


void Game::clean()
{
    std::cout<<"cleaning up!\n";
    TheInputHandler::Instance() -> clean();

    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void Game::update()
{
    //loop through objects and update
    m_pGameStateMachine -> update();
}

void Game::handleEvents()
{
    TheInputHandler::Instance() -> update();

    if(TheInputHandler::Instance() -> isKeyDown(SDL_SCANCODE_RETURN))
    {
        m_pGameStateMachine->changeState(new PlayState());
    }
}

void Game::setCurrentLevel(int currentLevel)
{
    m_currentLevel = currentLevel;
    if((m_currentLevel-1) < m_levelFiles.size())
    {
        m_pGameStateMachine->changeState(new BetweenLevelState());
    }
    else
    {
        m_pGameStateMachine->changeState(new GameOverState());
    }
    m_bLevelComplete = false;
}
