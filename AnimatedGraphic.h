#ifndef __AnimatedGraphic__
#define __AnimatedGraphic__

#include <iostream>
#include "SDLGameObject.h"
#include "GameObjectFactory.h"

class AnimatedGraphic : public SDLGameObject
{
public:
    AnimatedGraphic();
    virtual ~AnimatedGraphic() {}

    virtual void load(std::unique_ptr<LoaderParams> const &pParams);
    virtual void draw();
    virtual void update();
    virtual void clean();

private:
    int m_animSpeed;
    int m_numFrames;
};

class AnimatedGraphicCreator : public BaseCreator
{
public: 
    virtual GameObject* createGameObject() const
    {
        return new AnimatedGraphic();
    }
};

#endif
