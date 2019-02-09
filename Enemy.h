#ifndef __Enemy__
#define __Enemy__

#include <iostream>
#include <string>
#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "GameObjectFactory.h"

class Enemy : public SDLGameObject //inherit from sdlgameobject
{
public:
    virtual std::string type() { return "Enemy";}
protected:
    int m_health;
    Enemy() : SDLGameObject() {}
    virtual ~Enemy() {}
};
#endif
