#include"GameState.h"

class GameStateMachine
{
public:
    GameStateMachine() {}
    ~GameStateMachine() {}

    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();

    void update();
    void render();
    void clean();

	std::vector<GameState*>& getGameStates() { return m_gameStates; }

private:
    std::vector<GameState*> m_gameStates;
};

