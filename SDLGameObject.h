#ifndef __SDLGameObject__
#define __SDLGameObject__

#include <iostream>
#include <string>
#include "include/SDL2/SDL.h"
#include "LoaderParams.h"
#include "GameObject.h"
#include "vector2d.h"

class SDLGameObject : public GameObject
{
public: 
    //SDLGameObject(const LoaderParams* pParams);
    virtual ~SDLGameObject() {}

    virtual void draw() ; //draw game object
    virtual void update() ; //update game object
    virtual void clean() {} ;  //clean game object"
    virtual void load(std::unique_ptr<LoaderParams> const &pParams);

    virtual void collision() {}
    virtual std::string type() {return "SDLGameObject";}

protected:
    SDLGameObject();
    bool checkCollideTile(Vector2D newPos);
    void doDyingAnimation();

    int m_bulletFiringSpeed;
    int m_bulletCounter;

    int m_moveSpeed;

    int m_dyingTime;
    int m_dyingCounter;

    bool m_bPlayedDeathSound;

//shouldnt be here!
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;
    int m_width;
    int m_height;
};

#endif
