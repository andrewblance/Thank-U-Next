#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"
#include "TileLayer.h"

SDLGameObject::SDLGameObject() : GameObject(),
                                 m_bulletFiringSpeed(0),
                                 m_bulletCounter(0),
                                 m_moveSpeed(0),
                                 m_dyingTime(0),
                                 m_dyingCounter(0),
                                 m_bPlayedDeathSound(false),
                                 m_position(0,0),
                                 m_velocity(0,0),
                                 m_acceleration(0,0)
{
}

void SDLGameObject::draw()
{
    TextureManager::Instance() -> drawFrame(m_textureID,
        (Uint32)m_position.getX(), (Uint32)m_position.getY(),
        m_width, m_height, m_currentRow, m_currentFrame,
        TheGame::Instance() -> getRenderer(),
        m_angle, m_alpha);
   
}

void SDLGameObject::update()
{
    m_velocity += m_acceleration;
    m_position += m_velocity;
}

void SDLGameObject::load(std::unique_ptr<LoaderParams> const &pParams)
{
    m_position = Vector2D(pParams->getX(), pParams->getY());
    m_width = pParams -> getWidth();
    m_height = pParams -> getHeight();
    m_textureID = pParams -> getTextureID();
    m_numFrames = pParams -> getNumFrames();

//shouldnt be here!
    //m_currentRow = 1;
    m_currentFrame = 1;
    //m_velocity = Vector2D(0,0);
    //m_acceleration = Vector2D(0,0);
}

void SDLGameObject::doDyingAnimation()
{
    scroll(TheGame::Instance() -> getScrollSpeed());

    m_currentFrame = int(((SDL_GetTicks() / (1000/3) ) % m_numFrames));

    if(m_dyingCounter == m_dyingTime)
    {
        m_bDead = true;
    }
    m_dyingCounter++;
}

bool SDLGameObject::checkCollideTile(Vector2D newPos) 
{
    if(newPos.m_y + m_height >= TheGame::Instance()->getGameHeight() - 0)
    {
        return false;
    }
    if(newPos.m_x + m_width >= TheGame::Instance()->getGameWidth() - 0)
    {
        return false;
    }
    if(newPos.m_x  <= -100 )
    {
        return true;
    }  
    else
    { 
    for(std::vector<TileLayer*>::iterator it = m_pCollisionSafeLayers -> begin(); 
                        it != m_pCollisionSafeLayers -> end(); ++it)
    {
        TileLayer* pTileLayer = (*it);
        std::vector<std::vector<int> > tiles = pTileLayer -> getTileIDs();

        Vector2D layerPos = pTileLayer -> getPosition();

        int x, y, tileColumn, tileRow, tileid = 0;

        x = layerPos.getX() / pTileLayer->getTileSize();
        y = layerPos.getY() / pTileLayer->getTileSize();

        Vector2D startPos = newPos;
        startPos.m_x += 15;
        startPos.m_y += 20;
        Vector2D endPos(newPos.m_x + (m_width - 15), (newPos.m_y) + m_height - 4);

        for(int i = startPos.m_x; i < endPos.m_x; i++)
        {
            for(int j = startPos.m_y; j < endPos.m_y; j++)
            {
                tileColumn = i / pTileLayer->getTileSize();
                tileRow = j / pTileLayer->getTileSize();

                tileid = tiles[tileRow + y][tileColumn + x];
                if(tileid != 0)
                {
                    return true;
                }
            }
        }
    }
    return false;
    }
}

