#ifndef __ObjectLayer__
#define __ObjectLayer__

#include "Layer.h"
#include "GameObject.h"
#include <vector>
#include <iostream>

class ObjectLayer : public Layer
{
    public:
    virtual void update();
    virtual void render();

    std::vector<GameObject*>* getGameObjects()
    {
        return &m_gameObjects;
    }

    private:
    std::vector<GameObject*> m_gameObjects;
};

#endif
