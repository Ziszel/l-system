#include "../include/sdl-app.hpp"

SDL_Window *sdl_helper::p_window = NULL;
SDL_Renderer *sdl_helper::p_renderer = NULL;
float sdl_helper::program_running = false;
int sdl_helper::active_lsystem = -1;

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

void sdl_helper::Handle_Event(SDL_Event *event, std::vector<Lsystem*> lsystems)
{
    if (event->type == SDL_QUIT)
        program_running = false;
    // Detect if a key has been pressed
    // https://wiki.libsdl.org/SDL_KeyboardEvent
    if (event->type == SDL_KEYDOWN)
    {
        // get the SDL virtual key code to detect which key is pressed
        switch (event->key.keysym.sym)
        {
        case 'a':
            if (active_lsystem == lsystems.size() - 1) // this should match the count of the config files loaded - 1
            {
                active_lsystem = 0;
            }
            else { active_lsystem++; }

            std::cout << active_lsystem << "\n";

            SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 255); // make the bg black
            SDL_RenderClear(p_renderer); // clear the renderer ready for fresh drawing
            lsystems.at(active_lsystem)->Draw_Generation(); // draw the active l-system

            SDL_RenderPresent(p_renderer); // present the render to the screen
            break;

        default:
            break;
        }
    }
}
