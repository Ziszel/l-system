#include "../include/sdl-app.hpp"

SDL_Window* sdl_helper::p_window = NULL;
SDL_Renderer* sdl_helper::p_renderer = NULL;
float sdl_helper::program_running = false;

int sdl_helper::Init_SDL()
{
    // Initialize SDL, must be done before other calls
    // 'EVERYTHING' allows calls to ALL elements of SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL could not initialize! SDL_Error: \n"
                  << SDL_GetError();
        return -1;
    }

    // Set window context so that it can be displayed
    p_window = SDL_CreateWindow("Fractals", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (p_window == NULL)
    {
        std::cout << "Window could not be created! SDL_Error: \n"
                  << SDL_GetError();
        return -1;
    }

    // Create 2D Renderer
    p_renderer = SDL_CreateRenderer(p_window, -1, 0);

    program_running = true;

    return 0;
}

void sdl_helper::Handle_Event(SDL_Event *event)
{
    if (event->type == SDL_QUIT)
        program_running = false;

}
