#pragma once
#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <sstream>
#include "../include/rule.hpp"
#include "../include/turtle.hpp"

typedef struct Vector3
{
    float x;
    float y;
    float z;
} Vector3;

class Lsystem {
private:
    std::vector<Rule> rules;
    std::string current; // the axiom
    std::stringstream next; // holds each generation

    // Drawing relevant
    Turtle turtle;

    // editable values
    int iteration;
    float r, g, b, a;
    float theta;
    std::vector<Vector3> turtle_branch_data;

    // SDL specific
    SDL_Renderer* p_renderer;

public:
    Lsystem(std::string current, // the axiom
            int start_x,
            int start_y,
            float r,
            float g,
            float b,
            float a,
            double theta,
            float length,
            SDL_Renderer* p_renderer);

    std::vector<Rule> Populate_Rules();
    void Iterate_Generation();
    void Draw_Generation();
    int Get_Iteration();
};
