#include "CollisionManager.h"
#include "Collision.h"
#include "Player.h"
#include "TileLayer.h"


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
