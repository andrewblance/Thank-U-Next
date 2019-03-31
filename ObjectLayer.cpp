#include "ObjectLayer.h"
#include "GameObject.h"
#include "vector2d.h"
#include "Game.h"
#include "Level.h"

void ObjectLayer::update(Level *pLevel)
{
    m_collisionManager.checkPlayerEnemyCollision(pLevel->getPlayer(), 
                        (const std::vector<GameObject*>&)m_gameObjects);

    if(pLevel->getPlayer()->getPosition().getX() + pLevel->getPlayer()->getWidth() 
                        < TheGame::Instance()->getGameWidth())
	{
		m_collisionManager.checkPlayerTileCollision(pLevel->getPlayer(), 
                            pLevel->getCollidableLayers());
	}
    for(int i=0; i<m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> update();
    }

}

void ObjectLayer::render()
{
    for(int i=0; i<m_gameObjects.size(); i++)
    {
        m_gameObjects[i] -> draw();
    }
}
