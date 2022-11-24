#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <sstream>
#include "../include/rule.hpp"
#include "../include/turtle.hpp"
#include "../include/data-manager.hpp"

typedef struct Vector3
{
    float x;
    float y;
    float z;
} Vector3;

class Lsystem {
private:
    std::string current; // the current l-system string
    std::stringstream next; // used to build the next l-system generation

    Turtle turtle;
    std::vector<Vector3> turtle_branch_data; // stores the turtle pos and angle when branching
    Lsystem_Data* ls_data; // the data loaded from configuration files
    int turtle_start_x;
    int turtle_start_y;
    std::vector<Vector3> turtle_colours;
    uint current_colour = 0; // used for looping through the colours available
    std::string axiom; // store the axiom for resetting the 'current' variable on 'Clear_Lsystem()'

    // SDL specific
    SDL_Renderer* p_renderer;

public:
    Lsystem(int start_x,
            int start_y,
            Lsystem_Data* ls_data,
            SDL_Renderer* p_renderer);

    void Iterate_Generation(); // iterates one generation
    void Process_Lsystem(int iterations); // will call Iterate_Generation() by the number of iterations passed in
    void Clear_Lsystem();
    void Draw_Generation();
    void Change_Turtle_Colour();
    void Populate_Turtle_Colours(); // Called at the beginning to ensure turtle_colours has lots of colours to draw!
};
