#pragma once
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "../include/l-system.hpp"

namespace sdl_helper {

    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 900;

    // https://stackoverflow.com/questions/12511044/bss0x0-multiple-definition-of-proxies
    // https://www.freecodecamp.org/news/extern-keyword-function-tutorial/
    // Window context
    extern SDL_Window* p_window;
    // Always favour renderer over surface in modern SDL2
    extern SDL_Renderer* p_renderer;
    extern float program_running;
    extern int active_lsystem;

    int Init_SDL();
    void Handle_Event(SDL_Event* event, std::vector<Lsystem*> lsystems);

}