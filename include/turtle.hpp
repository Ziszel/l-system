#pragma once
#include <math.h>
#include "SDL2/SDL.h"
#include "iostream"

class Turtle {
private:
    SDL_Renderer* p_renderer;
    bool is_pen_down;
    float x, y, angle, length;
    int r, g, b, a;

public:
    // Constructors & Destructors
    Turtle();

    // SDL specific
    void Set_Renderer(SDL_Renderer* p_renderer);
    
    // Pen controls
    void Pen_Down();
    void Pen_Up();
    void Set_Pen_Colour(int r, int g, int b, int a);

    // Movement controls
    void Set_Angle(float angle);
    void Set_Length(float length); // how far forward the turtle will move
    void Rotate_Left(float angle);
    void Rotate_Right(float angle);
    void Look_At(float x, float y);
    void Step(); // Advance the turtle forward, taking into account angle, and pen

    // Utility functions
    float Deg_To_Rad(float degrees);
    void Set_Pos(float x, float y);
    float Get_X();
    float Get_Y();
    float Get_Angle();
    float Get_Length();
};