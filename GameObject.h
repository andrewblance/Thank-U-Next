#ifndef __GameObject__
#define __GameObject__

#include <iostream>
#include <string>
#include "include/SDL2/SDL.h"
#include "LoaderParams.h"
#include "vector2d.h"

class TileLayer;

class GameObject
{
public:
    virtual ~GameObject() {}
    virtual void draw()   = 0; //draw game object
    virtual void update() = 0; //update game object
    virtual void clean()  = 0;  //clean game object"
    virtual void collision() =0; //collision

    //new load function
    virtual void load(std::unique_ptr<LoaderParams> const &pParams) = 0;

    virtual std::string type() = 0; //type of object
    Vector2D& getPosition() { return m_position; }
    int getWidth() { return m_width; }
    int getHeight() { return m_height; }
    void scroll(float scrollSpeed) { m_position.setX(m_position.getX()
                        - scrollSpeed); }
    bool updating() { return m_bUpdating;} //object being updated?
    bool dead() { return m_bDying; } //dying?
    bool dying() { return m_bDead; } //dead?
    void setUpdating(bool updating) { m_bUpdating = updating;}

    void setCollisionLayers(std::vector<TileLayer*>* layers) 
                    { m_pCollisionLayers = layers; }

protected:
    GameObject() : m_position(0,0),
                   m_velocity(0,0),
                   m_acceleration(0,0),
                   m_width(0),
                   m_height(0),
                   m_currentRow(0),
                   m_currentFrame(0),
                   m_bUpdating(false),
                   m_bDead(false),
                   m_bDying(false),
                   m_angle(0),
                   m_alpha(255)
    {}
    // movement variables
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;

    // size variables
    int m_width;
    int m_height;

    // animation variables
    int m_currentRow;
    int m_currentFrame;
    int m_numFrames;
    std::string m_textureID;

    //boolean variables
    bool m_bUpdating;
    bool m_bDead;
    bool m_bDying;

    //rotation
    double m_angle;
    
    //blending
    int m_alpha;

    std::vector<TileLayer*>* m_pCollisionLayers;
};

#endif
