#include "MenuButton.h"
#include "InputHandler.h"
#include "SoundManager.h"

MenuButton::MenuButton() : SDLGameObject(), m_callback(0), m_bReleased(true)
{
    //m_currentFrame = MOUSE_OUT;
}

void MenuButton::draw()
{
    SDLGameObject::draw();
}

void MenuButton::update()
{
    Vector2D* pMousePos = TheInputHandler::Instance() -> getMousePosition();

    if(pMousePos->getX() < (m_position.getX() + m_width)
    && pMousePos->getX() > m_position.getX()
    && pMousePos->getY() < (m_position.getY() + m_height)
    && pMousePos->getY() > m_position.getY())
    {
        if(TheInputHandler::Instance() -> getMouseButtonState(LEFT)
        && m_bReleased)
        {
            TheSoundManager::Instance()->playSound("boom", 0);
            m_currentFrame = CLICKED; 
            m_callback();
            m_bReleased = false;
        }
        else if(!TheInputHandler::Instance() -> getMouseButtonState(LEFT))
        {
            m_bReleased = true;
            m_currentFrame = MOUSE_OVER;
        }
    }
    else
    {
        m_currentFrame = MOUSE_OUT;
    }
}
void MenuButton::clean()
{
    SDLGameObject::clean();
}

void MenuButton::load(std::unique_ptr<LoaderParams> const &pParams)
{
    SDLGameObject::load(pParams);
    m_callbackID = pParams -> getCallbackID();
   // std::cout<<m_callbackID << "\n";
    m_currentFrame = MOUSE_OUT;
}
