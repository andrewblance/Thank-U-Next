#ifndef __GameOverState__
#define __GameOverState__

#include <iostream>
#include <vector>
#include "MenuState.h"
#include "GameObject.h"
#include "Level.h"

class GameObject;

class GameOverState : public MenuState
{
public:
    virtual ~GameOverState() {}
    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_gameOverID; }
    virtual void setCallbacks(const std::vector<Callback>& callbacks);

private:
    static void s_gameOverToMain();
    static void s_restartPlay();
    static void s_exitfromOver();
    Level* pLevel;
    static const std::string s_gameOverID;
    std::vector<GameObject*> m_gameObjects;
};

#endif
