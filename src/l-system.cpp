#include "../include/l-system.hpp"

// turtle must be initialised before constructor call of Lsystem, constructor list used for this purpose
Lsystem::Lsystem(std::string current, int start_x, int start_y,
                float r, float g, float b, float a, double theta, float length,
                SDL_Renderer* p_renderer) : turtle()
{
    this->rules = Populate_Rules();
    this->current = current;
    this->iteration = 0;
    this->theta = theta;
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;

    // Initial turtle setup
    this->turtle.Pen_Down();
    this->turtle.Set_Renderer(p_renderer);
    this->turtle.Set_Length(length);
    turtle.Set_Pos(start_x, start_y); // turtle start pos
}

std::vector<Rule> Lsystem::Populate_Rules()
{
    std::vector<Rule> return_value;

    Rule rule_1 = {'F', "F+F-F-FF+F+F-F"};

    return_value.push_back(rule_1);

    return return_value;
}

void Lsystem::Iterate_Generation()
{
        std::cout << current << "\n";
        // completely erase stringstream
        this->next.clear(); this->next.str(std::string());
        // Iterate generation
        for(auto i: current)
        {
            for(auto r : rules)
            {
                if(i == r.Get_Input())
                {
                    this->next << r.Get_Output();
                }
            }
        }
        current = next.str();
        iteration++;
        //this->turtle.Set_Length(this->turtle.Get_Length() / 4);
}

void Lsystem::Draw_Generation()
{
    for (auto c : current)
    {
        switch(c)
        {
            case 'F': {
                this->turtle.Pen_Down();
                this->turtle.Step();
                break;
            }
            case 'f': {
                this->turtle.Pen_Up();
                this->turtle.Step();
                break;
            }
            case '-': {
                this->turtle.Rotate_Left(theta);
                break;
            }
            case '+': {
                this->turtle.Rotate_Right(theta);
                break;
            }
            case '[': {
                // http://www.paulbourke.net/fractals/lsys/
                // save the current position and current angle for branching
                this->turtle_branch_data.push_back({this->turtle.Get_X(),
                    this->turtle.Get_Y(), 
                    this->turtle.Get_Angle()});
                break;
            }
            case ']': {
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

}

int Lsystem::Get_Iteration()
{
    return iteration;
}
