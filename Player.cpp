#include "Player.h"
#include "GameObject.h"
#include "InputHandler.h"
#include "Game.h"

Player::Player(): SDLGameObject(),
m_invulnerable(false),
m_invulnerableTime(200),
m_invulnerableCounter(0)
{
}

void Player::draw()
{
    if(!dirFace)
    {
        TextureManager::Instance() -> drawFrame(m_textureID,
        (Uint32)m_position.getX(), (Uint32)m_position.getY(),
        m_width, m_height, m_currentRow, m_currentFrame,
        TheGame::Instance() -> getRenderer(),
        m_angle, m_alpha);
    }
    else
    { 
        TextureManager::Instance() -> drawFrame(m_textureID,
        (Uint32)m_position.getX(), (Uint32)m_position.getY(),
        m_width, m_height, m_currentRow, m_currentFrame,
        TheGame::Instance() -> getRenderer(),
        m_angle, m_alpha, SDL_FLIP_HORIZONTAL);
    }
}

void Player::update()
{
    if(TheGame::Instance() -> getLevelComplete()) //if level is complete
    {
        if((m_position.getX()) >= TheGame::Instance() -> getGameWidth())
        {
            TheGame::Instance() -> setCurrentLevel(TheGame::Instance()
                                -> getCurrentLevel() + 1);
        }
        else
        {
            m_velocity.setY(0);
            m_velocity.setX(3);
            SDLGameObject::update();
            handleAnimation();
        }
    }
    else
    {
        if(!m_bDying)   //not dying
        {
            m_velocity.setX(0);
            m_velocity.setY(0);

            handleInput();
            //SDLGameObject::update();
           
            if(checkCollideTile(m_position))
            {
                std::cout<<"coll" << "\n";
            }
            handleMovement(m_velocity);
            handleAnimation();
//this bit, nope:
            if((m_position.getX()+30) >= TheGame::Instance() -> getGameWidth())
            {
                TheGame::Instance()->setLevelComplete(true);
            }
            //std::cout << m_position.getX() << "\n";
        }
        else  //if doing death animation
        {
            m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
            if(m_dyingCounter == m_dyingTime)
            {
                ressurect();
            }
            m_dyingCounter++;
        }
    }
}

void Player::clean()
{
}

void Player::handleInput()
{
    if(TheInputHandler::Instance() -> isKeyDown(SDL_SCANCODE_RIGHT) ||
       TheInputHandler::Instance() -> isKeyDown(SDL_SCANCODE_D))
    {
        dirFace = true;
        m_velocity.setX(2);
    }
    if(TheInputHandler::Instance() -> isKeyDown(SDL_SCANCODE_LEFT) ||
       TheInputHandler::Instance() -> isKeyDown(SDL_SCANCODE_A))
    {
        dirFace = false;
        m_velocity.setX(-2);
    }
    if(TheInputHandler::Instance() -> isKeyDown(SDL_SCANCODE_UP) ||
       TheInputHandler::Instance() -> isKeyDown(SDL_SCANCODE_W))
    {
        m_velocity.setY(-2);
    }
    if(TheInputHandler::Instance() -> isKeyDown(SDL_SCANCODE_DOWN) ||
       TheInputHandler::Instance() -> isKeyDown(SDL_SCANCODE_S))
    {
        m_velocity.setY(2);
    }

}

void Player::load(std::unique_ptr<LoaderParams> const &pParams)
{
    dirFace = true;
    SDLGameObject::load(std::move(pParams));
}

void Player::ressurect()
{
    TheGame::Instance() -> setPlayerLives(TheGame::Instance()
                        -> getPlayerLives() - 1);

    m_position.setX(10);
    m_position.setY(200);
    m_bDying = false;

    m_textureID = "player";

    m_currentFrame = 0;
    m_numFrames = 12;
    m_width = 80;
    m_height = 80;

    m_dyingCounter = 0;
    m_invulnerable = true;
}

void Player::handleAnimation()
{
    if(m_invulnerable)
    {
        if(m_invulnerableCounter == m_invulnerableTime)
        {
            m_invulnerable = false;
            m_invulnerableCounter = 0;
            m_alpha = 255;
        }
        else
        {
            if(m_alpha == 255)
            {
                m_alpha = 0;
            }
            else
            {
                m_alpha = 255;
            }
        }
        m_invulnerableCounter++;
    }

    if(!m_bDead)
    {
        if(m_velocity.getX() == 0)
        {
            m_angle = 0.0;
        }
        else if(!dirFace)
        {
            m_angle = -10.0;
        }
        else if(dirFace)
        { 
            m_angle = 10.0;
        }
    }
    m_currentFrame = int(((SDL_GetTicks() / (100)) % m_numFrames));
}



void Player::handleMovement(Vector2D velocity)
{
    Vector2D newPos = m_position;
    Vector2D newPos_ = m_position;
    
    if(!scrollTrue)
    {
        newPos.m_x  = m_position.m_x + velocity.m_x;
        if(!checkCollideTile(newPos))
        {
        // no collision, add to the actual x position
            m_position.m_x = newPos.m_x;
        }
        else
        {
        // collision, stop x movement
            m_velocity.m_x = 0;
        }
    }
    else if (m_velocity.m_x > 0)
    {
        newPos.m_x = m_position.m_x + m_velocity.m_x;
        newPos_.m_x = m_position.m_x + 32;

        if(!checkCollideTile(newPos_))
        {
        // no collision, add to the actual x position
            m_position.m_x = newPos.m_x;
        }
     //   else if(m_velocity.m_x > 0)
        else
        {
            m_velocity.setX(TheGame::Instance()->getScrollSpeed());
            m_position.m_x -= m_velocity.m_x;
         }
    }
    else if (m_velocity.m_x < 0)
    {
        newPos.m_x = m_position.m_x + m_velocity.m_x;
        newPos_.m_x = m_position.m_x  - 32;

        if(!checkCollideTile(newPos_))
        {
        // no collision, add to the actual x position
            m_position.m_x = newPos.m_x;
        }
     //   else if(m_velocity.m_x > 0)
        else
        {
            m_velocity.setX(TheGame::Instance()->getScrollSpeed());
            m_position.m_x -= m_velocity.m_x;
         }
    }
    else
    {
        newPos.m_x = m_position.m_x + 8;
        bool jjj = checkCollideTile(newPos);
        while(jjj == true)
        {            
            m_velocity.setX(TheGame::Instance()->getScrollSpeed());
            m_position.m_x -= m_velocity.m_x;
            jjj = checkCollideTile(m_position);
        }
    }

//do agaib but for y 
    newPos = m_position;
    // add velocity to y position
    newPos.m_y += velocity.m_y;

    // check if new y position would collide with a tile
    if(!checkCollideTile(newPos))
    {
        // no collision, add to the actual x position
        m_position.m_y = newPos.m_y;
    }
    else
    {
        // collision, stop y movement
        m_velocity.m_y = 0;
    } 
}
