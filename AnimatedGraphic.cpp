#include "AnimatedGraphic.h"

AnimatedGraphic::AnimatedGraphic() :
SDLGameObject()
{
}

void AnimatedGraphic::draw()
{
    SDLGameObject::draw();
}

void AnimatedGraphic::update()
{ 
    m_currentFrame = int(((SDL_GetTicks() / (1000 / m_animSpeed)) % m_numFrames));
}

void AnimatedGraphic::clean()
{
    SDLGameObject::clean();
}

void AnimatedGraphic::load(std::unique_ptr<LoaderParams> const &pParams)
{
    SDLGameObject::load(pParams);
    m_numFrames = pParams->getNumFrames();
    m_animSpeed = pParams->getAnimSpeed();
}
