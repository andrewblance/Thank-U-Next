#ifndef __InputHandler__
#define __InputHandler__


#include "include/SDL2/SDL.h"
#include <iostream>
#include<vector>
#include "vector2d.h"

enum mouse_buttons
{
    LEFT=0,
    MIDDLE=1,
    RIGHT=2
};

class InputHandler
{
public:
    static InputHandler* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new InputHandler();
        }
        return s_pInstance;
    }

    void initialiseJoysticks(); //initialise the joysticks
    bool joysticksInitialised() 
    {
        return m_bJoysticksInitialised;
    }
    bool getButtonState(int joy, int buttonNumber) const;

    bool getMouseButtonState( int buttonNumber) const
    {
        return m_mouseButtonStates[buttonNumber];
    }

    // keyboard events
    bool isKeyDown(SDL_Scancode key) const;
   
    Vector2D* getMousePosition()
    {
        return m_mousePosition;
    }

    //grab stick values from pairs
    int xvalue(int joy, int stick);
    int yvalue(int joy, int stick);

    void reset();

    void update();
    void clean();

private:
    InputHandler();
    ~InputHandler();
    static InputHandler* s_pInstance;

    // private functions to handle different event types
    // handle keyboard events
    void onKeyDown();
    void onKeyUp();
    // handle mouse events
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);
    // handle joysticks events
    void onJoystickAxisMove(SDL_Event& event);
    void onJoystickButtonDown(SDL_Event& event);
    void onJoystickButtonUp(SDL_Event& event);

    // keyboard specific
    const Uint8* m_keystates;

    std::vector<SDL_Joystick*> m_joysticks; //vec to store gamepads
    std::vector<std::pair<Vector2D*, Vector2D*> > m_joystickValues; //store stick stuff
    std::vector<std::vector<bool> > m_buttonStates; //button vec
    std::vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePosition;
    bool m_bJoysticksInitialised;
    static const int m_joystickDeadZone = 10000;
};
typedef InputHandler TheInputHandler;

#endif
                
