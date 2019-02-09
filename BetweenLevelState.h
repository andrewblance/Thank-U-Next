#ifndef __BetweenLevelState__
#define __BetweenLevelState__

#include "MenuState.h"
#include "GameObject.h"
#include "Level.h"

class BetweenLevelState : public MenuState
{
public:
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_menuID; }

private:
    virtual void setCallbacks(const std::vector<Callback>&
    callbacks);
    Level* pLevel;

    static void s_contToPlay();
    static void s_exitFromCont();
    static void s_contToMain();

    static const std::string s_menuID;
    std::vector<GameObject*> m_gameObjects;
};

#endif
