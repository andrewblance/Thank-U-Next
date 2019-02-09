#ifndef __Player__
#define __Player__

#include <iostream>
#include <string>
#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "GameObjectFactory.h"

class Player : public SDLGameObject //inherit from sdlgameobject
{
public:
    Player();
    virtual ~Player() {};

    virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();
    virtual void collision(){};

    virtual std::string type() { return "Player"; }

private:
    void handleInput();
    void ressurect();
    void handleAnimation();
    void handleMovement(Vector2D velocity);

    int m_invulnerable;
    int m_invulnerableTime;
    int m_invulnerableCounter;
};

class PlayerCreator : public BaseCreator
{
    GameObject* createGameObject() const
    {
        return new Player();
    }
};

#endif
