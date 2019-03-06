#ifndef __Collision__
#define __Collision__

#include "include/SDL2/SDL.h"
#include "vector2d.h"

const static int s_buffer = 4;

static bool RectRect(SDL_Rect* A, SDL_Rect* B)
{
    int aHBuf = A -> h / s_buffer;
    int aWBuf = A -> w / s_buffer;

    int bHBuf = B -> h / s_buffer;
    int bWBuf = B -> w / s_buffer;

    //if bottom of a is less than top of b => no collision
    if( (A -> y + A -> h) - aHBuf <= B -> y + bHBuf) {return false;}

    //if top of a is more than top of b => no collision
    if( A -> y +  aHBuf            >= (B -> y + B -> h) -  bHBuf) {return false;}

    //if right of a is less than left of b => no collision
    if( (A -> x + A -> w) - aWBuf  <= B -> x + bWBuf) {return false;}

    //if bottom of a is less than top of b => no collision
    if( A -> x + aWBuf             >= (B -> x + B -> w) - bWBuf) {return false;}

    return true;
}
#endif
