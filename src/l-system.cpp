#include "../include/l-system.hpp"

// Two types of rewriting systems (edge and node), both are similarly implemented:
//https://stackoverflow.com/questions/27858249/l-system-node-rewriting-example
// turtle must be initialised before constructor call of Lsystem, constructor list used for this purpose
Lsystem::Lsystem(int start_x, int start_y, float length, Lsystem_Data *ls_data,
                 SDL_Renderer *p_renderer) : turtle()
{
    this->ls_data = ls_data;
    this->current = this->ls_data->axiom;
    this->iteration = 0;

    // Initial turtle setup
    this->turtle.Pen_Down();
    this->turtle.Set_Renderer(p_renderer);
    this->turtle.Set_Length(length);
    this->turtle.Set_Pen_Colour(ls_data->red, ls_data->blue, ls_data->green, ls_data->alpha);

    this->turtle_start_x = start_x;
    this->turtle_start_y = start_y;
    this->turtle.Set_Pos(turtle_start_x, turtle_start_y); // turtle start pos
}

// void Lsystem::Reset()
// {
//     this->ls_data = ls_data;
//     this->current = this->ls_data->axiom;
//     this->iteration = 0;

//     // Initial turtle setup
//     this->turtle.Pen_Down();
//     this->turtle.Set_Renderer(p_renderer);
//     this->turtle.Set_Length(length);
//     this->turtle.Set_Pen_Colour(ls_data->red, ls_data->blue, ls_data->green, ls_data->alpha);
//     turtle.Set_Pos(start_x, start_y); // turtle start pos
// }

void Lsystem::Iterate_Generation()
{
    // completely erase stringstream
    this->next.clear(); 
    this->next.str(std::string());
    // Iterate generation
    for (auto i : this->current)
    {
        int wasRule = 0;
        for (auto r : this->ls_data->ruleset)
        {
            if (i == r.Get_Input())
            {
                this->next << r.Get_Output();
                wasRule++;
            }
        }
        if (wasRule == 0)
        {
            this->next << i;
        }
    }
    this->current = this->next.str();
    this->iteration++;
}

void Lsystem::Draw_Generation()
{
    for (auto c : current)
    {
        switch (c)
        {
            case 'F':
            {
                // ensure a line is drawn and move the turtle forward
                this->turtle.Pen_Down();
                this->turtle.Step();
                break;
            }
            case 'f':
            {
                // ensure a line is not drawn and move the turtle forward
                this->turtle.Pen_Up();
                this->turtle.Step();
                break;
            }
            case '-':
            {
                this->turtle.Rotate_Left(this->ls_data->theta);
                break;
            }
            case '+':
            {
                this->turtle.Rotate_Right(this->ls_data->theta);
                break;
            }
            case '[':
            {
                // http://www.paulbourke.net/fractals/lsys/
                // save the current position and current angle for branching
                this->turtle_branch_data.push_back({this->turtle.Get_X(),
                                                    this->turtle.Get_Y(),
                                                    this->turtle.Get_Angle()});
                break;
            }
            case ']':
            {
                // ] means to restore the state of the turtle to before the branch
                // commands took place, and pop the stack
                Vector3 return_values = this->turtle_branch_data.back();
                this->turtle.Set_Pos(return_values.x, return_values.y);
                this->turtle.Set_Angle(return_values.z);

                this->turtle_branch_data.pop_back();
                break;
            }
        }
    }
    // Reset the turtle position for the next time the l-system needs to be drawn
    this->turtle.Set_Pos(turtle_start_x, turtle_start_y);
    this->turtle.Set_Angle(this->turtle.Deg_To_Rad(-90));
}

int Lsystem::Get_Iteration()
{
    return iteration;
}
