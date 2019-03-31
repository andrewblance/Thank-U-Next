#include "CollisionManager.h"
#include "Collision.h"
#include "Player.h"
#include "TileLayer.h"
#include "Enemy.h"


void CollisionManager::checkPlayerTileCollision(Player* pPlayer, 
                    const std::vector<TileLayer*>& collisionLayers)
{
    for(std::vector<TileLayer*>::const_iterator it = collisionLayers.begin(); 
                        it != collisionLayers.end(); ++it)
    {
        TileLayer* pTileLayer = (*it);
        std::vector<std::vector<int> > tiles = pTileLayer->getTileIDs();
        
        Vector2D layerPos = pTileLayer->getPosition();
        
        int x, y, tileColumn, tileRow, tileid = 0;
        
        x = layerPos.getX() / pTileLayer->getTileSize();
        y = layerPos.getY() / pTileLayer->getTileSize();

        Vector2D newPos = pPlayer -> getPosition() +
                            pPlayer -> getVelocity();

        Vector2D startPos = newPos;
        startPos.m_x += 15;
        startPos.m_y += 20;
        Vector2D endPos(newPos.m_x + (80 - 15), (newPos.m_y) + 80 - 4);

        for(int i = startPos.m_x; i < endPos.m_x; i++)
        {
            for(int j = startPos.m_y; j < endPos.m_y; j++)
            {
                tileColumn = i / pTileLayer->getTileSize();
                tileRow = j / pTileLayer->getTileSize();

                tileid = tiles[tileRow + y][tileColumn + x];

                if(tileid != 0)
                {
                    std::cout<< "hi" << "\n";
                    pPlayer -> collision();
                }
            }
        }    
    }
}

void CollisionManager::checkPlayerEnemyCollision(Player* pPlayer, const std::vector<GameObject*> &objects)
{
    SDL_Rect* pRect1 = new SDL_Rect();
    pRect1->x = pPlayer->getPosition().getX();
    pRect1->y = pPlayer->getPosition().getY();
    pRect1->w = pPlayer->getWidth();
    pRect1->h = pPlayer->getHeight();

    for(int i = 0; i < objects.size(); i++)
    {
        std::cout<<objects[i]->type() << "\n";
        if(objects[i]->type() != std::string("Enemy"))// || !objects[i]->updating())
        {
            continue;
        }

        SDL_Rect* pRect2 = new SDL_Rect();
        pRect2->x = objects[i]->getPosition().getX();
        pRect2->y = objects[i]->getPosition().getY();
        pRect2->w = objects[i]->getWidth();
        pRect2->h = objects[i]->getHeight();
        
        if(RectRect(pRect1, pRect2))
        {
            std::cout<<"collision!!!!!!" << "\n";
            if(!objects[i]->dead() && !objects[i]->dying())
            {
                pPlayer->collision();
            }
        }
        delete pRect2;
    }
    delete pRect1;
}
