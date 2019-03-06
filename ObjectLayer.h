#ifndef __ObjectLayer__
#define __ObjectLayer__

#include "Layer.h"
#include "GameObject.h"
#include <vector>
#include <iostream>
#include "CollisionManager.h"

class ObjectLayer : public Layer
{
    public:
    virtual void update(Level* pLevel);
    virtual void render();

    std::vector<GameObject*>* getGameObjects()
    {
        return &m_gameObjects;
    }

    private:
    std::vector<GameObject*> m_gameObjects;
    CollisionManager m_collisionManager;
};

#endif
