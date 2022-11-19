#include "../include/turtle.hpp"

Turtle::Turtle()
{
    p_renderer = NULL;
    x = 0.0f;
    y = 0.0f;
    angle = Deg_To_Rad(-90); // ensure the turtle draws from bottom to top
    length = 0.0f;
    is_pen_down = false;    
    r = 255;
    g = 255;
    b = 255;
    a = 255;

}

void Turtle::Set_Renderer(SDL_Renderer* p_renderer)
{
    this->p_renderer = p_renderer;
}

void Turtle::Pen_Down() { this->is_pen_down = true; }
void Turtle::Pen_Up() { this->is_pen_down = false; }

void Turtle::Set_Pen_Colour(int r, int g, int b, int a)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Turtle::Set_Angle(float angle) { this->angle = angle; }
void Turtle::Set_Length(float length) { this->length = length; }

void Turtle::Rotate_Left(float angle) 
{
    this->angle -= Deg_To_Rad(angle);
}

void Turtle::Rotate_Right(float angle) 
{
    this->angle += Deg_To_Rad(angle);
}

// Required for certain types of fractals.
// Currently unused
void Turtle::Look_At(float x, float y)
{
    float delta_x = x - this->x;
    float delta_y = y - this->y;

    // If x or y are == 0, can't divide by 0
    if (delta_x == 0.0f)
    {
        if (delta_y > 0.0f) // angle must be 90
        {
            this->angle = M_PI / 2.0; // pi / 2 = 90 degrees (in rad)
        }
        // angle must be 270
        else { this->angle = M_PI + (M_PI / 2.0f); } // 180 + 90 = 270 degrees (in rad)
    }
    else 
    {
        // the arc tangent of the change in y / by the change in x
        // gives the angle between where the turtle is, and where it is to look
        this->angle = atan(delta_y / delta_x);
    }
    // If x is less than 0, we flip the angle (by 180) to find the correct angle
    if (delta_x < 0.0f)
    {
        this->angle += M_PI;
    }
}

void Turtle::Step()
{
    float start_x = this->x;
    float start_y = this->y;
    float end_x = start_x + (cos(this->angle) * this->length);
    float end_y = start_y + (sin(this->angle) * this->length);

    this->x = end_x;
    this->y = end_y;

    if (this->is_pen_down)
    {
        SDL_SetRenderDrawColor(this->p_renderer, this->r, this->g, this->b, this->a);
        SDL_RenderDrawLine(this->p_renderer,
        start_x, start_y,
        end_x, end_y);
    }
}

float Turtle::Deg_To_Rad(float angle) { return angle * (M_PI / 180.0); }
void Turtle::Set_Pos(float x, float y) { this->x = x; this->y = y; }
float Turtle::Get_X() { return this->x; }
float Turtle::Get_Y() { return this->y; }
float Turtle::Get_Angle() { return this->angle; }
float Turtle::Get_Length() { return this->length; }