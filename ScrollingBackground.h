#ifndef __ScrollingBackground__
#define __ScrollingBackground__

#include <iostream>
#include "GameObjectFactory.h"
#include "SDLGameObject.h"

class ScrollingBackground : public SDLGameObject
{
public:
    
    virtual ~ScrollingBackground() {}
    ScrollingBackground();
    
    virtual void draw();
    virtual void update();
    virtual void clean();
    
    virtual void load(std::unique_ptr<LoaderParams> const &pParams);

    void setMapWidth(int mapWidth) { m_mapWidth = mapWidth; }
    void setTileSize(int tileSize) { m_tileSize = tileSize; }
    
private:
    
    int m_scrollSpeed;
    
    int count;
    int maxcount;
    
    SDL_Rect m_srcRect1;
    SDL_Rect m_srcRect2;
    
    SDL_Rect m_destRect1;
    SDL_Rect m_destRect2;
    
    int m_srcRect1Width;
    int m_srcRect2Width;
    
    int m_destRect1Width;
    int m_destRect2Width;

    int m_mapWidth;
    int m_tileSize;
};

class ScrollingBackgroundCreator : public BaseCreator
{
public:
    
    virtual GameObject* createGameObject() const
    {
        return new ScrollingBackground();
    }
};

#endif
