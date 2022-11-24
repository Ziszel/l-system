#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "../include/l-system.hpp"
#include "../include/data-manager.hpp"

namespace sdl_helper {

    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;

    // https://stackoverflow.com/questions/12511044/bss0x0-multiple-definition-of-proxies
    // https://www.freecodecamp.org/news/extern-keyword-function-tutorial/
    // Window context
    extern SDL_Window* p_window;
    // Always favour renderer over surface in modern SDL2
    extern SDL_Renderer* p_renderer;
    extern float program_running;
    extern size_t active_lsystem; // to avoid different signedness comparisons, use size_of (comparing against unsigned long)
    extern int iterations;

    int Init_SDL();
    void Create_Lsystems();
    void Handle_Event(SDL_Event* event, std::vector<Lsystem*> lsystems);

}