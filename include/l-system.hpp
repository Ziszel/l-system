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
    std::vector<Vector3> turtle_branch_data;
    Lsystem_Data* ls_data;
    int iteration;
    int turtle_start_x;
    int turtle_start_y;
    std::vector<Vector3> turtle_colours;
    int current_colour = 0;

    // SDL specific
    SDL_Renderer* p_renderer;

public:
    Lsystem(int start_x,
            int start_y,
            Lsystem_Data* ls_data,
            SDL_Renderer* p_renderer);

    void Iterate_Generation();
    void Draw_Generation();
    int Get_Iteration();
    void Change_Turtle_Colour();
    void Populate_Turtle_Colours();
};
