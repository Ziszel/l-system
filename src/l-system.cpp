#include "../include/l-system.hpp"

// Two types of rewriting systems (edge and node), both are similarly implemented:
//https://stackoverflow.com/questions/27858249/l-system-node-rewriting-example
// turtle must be initialised before constructor call of Lsystem, constructor list used for this purpose
Lsystem::Lsystem(int start_x, int start_y, Lsystem_Data *ls_data,
                 SDL_Renderer *p_renderer) : turtle()
{
    this->ls_data = ls_data;
    this->axiom = this->ls_data->axiom;
    this->current = axiom;
    this->Populate_Turtle_Colours();

    // Initial turtle setup
    this->turtle.Pen_Down();
    this->turtle.Set_Renderer(p_renderer);
    this->turtle.Set_Length(this->ls_data->line_length);
    this->turtle.Set_Pen_Colour(ls_data->red, ls_data->blue, ls_data->green, ls_data->alpha);

    this->turtle_start_x = start_x;
    this->turtle_start_y = start_y;
    this->turtle.Set_Pos(turtle_start_x, turtle_start_y); // turtle start pos
}

void Lsystem::Iterate_Generation()
{
    // completely erase stringstream
    this->next.clear(); 
    this->next.str(std::string());
    // Iterate generation, for each character in the l-system string, either switch it out for a character set provided
    // by a rule, or store it as is (it is a constant)
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
        // this ensures constants are added after a rule check
        if (wasRule == 0)
        {
            this->next << i;
        }
    }
    // iterate current to equal the next generation
    this->current = this->next.str();
}

void Lsystem::Process_Lsystem(int iterations)
{
    for (int i = 0; i <= iterations; ++i)
    {
        this->Iterate_Generation();
    }
}

void Lsystem::Clear_Lsystem()
{
    this->current = axiom;
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

void Lsystem::Populate_Turtle_Colours()
{
    // red
    Vector3 colour = {255, 0, 0};
    this->turtle_colours.push_back(colour);

    // green
    colour = {0, 255, 0};
    this->turtle_colours.push_back(colour);

    // blue
    colour = {0, 0, 255};
    this->turtle_colours.push_back(colour);

    // yellow
    colour = {255, 255, 0};
    this->turtle_colours.push_back(colour);

    // purple
    colour = {128, 0, 128};
    this->turtle_colours.push_back(colour);

    // cyan
    colour = {0, 255, 255};
    this->turtle_colours.push_back(colour);

    // white
    colour = {255, 255, 255};
    this->turtle_colours.push_back(colour);
}

void Lsystem::Change_Turtle_Colour()
{
    // check if we are at the end of the list, and if so go to the first colour
    if (this->current_colour == this->turtle_colours.size())
    {
        this->current_colour = 0;
    }

    int r = this->turtle_colours.at(current_colour).x;
    int g = this->turtle_colours.at(current_colour).y;
    int b = this->turtle_colours.at(current_colour).z;

    this->turtle.Set_Pen_Colour(r, g, b, 255);

    this->current_colour++;
}