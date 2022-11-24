#include "../include/sdl-app.hpp"

SDL_Window *sdl_helper::p_window = NULL;
SDL_Renderer *sdl_helper::p_renderer = NULL;
float sdl_helper::program_running = false;
size_t sdl_helper::active_lsystem = 100; // 100 will be replaced instantly to 0 on first call, large number so it is obvious
int sdl_helper::iterations = 5;

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
    p_window = SDL_CreateWindow("L-System-Viewer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
        // BUG
        // These two commands along with SDL_Present(p_renderer) are called on every case, so I've used them here to
        // avoid duplication, HOWEVER this will cause a black screen if no key in the cases is pressed.
        SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 255); // make the bg black
        SDL_RenderClear(p_renderer); // clear the renderer ready for fresh drawing
        // get the SDL virtual key code to detect which key is pressed
        switch (event->key.keysym.sym)
        {
        case 'a':
            // active_lsystem counts from 0 to the size of the lsystem vector passed in
            // this allows me to access a specific lsystem, and each time a key is pressed
            // cycle through them, drawing only the 'active' lsystem
            if (active_lsystem >= lsystems.size() - 1) // this should match the count of the config files loaded - 1
            {
                active_lsystem = 0;
            }
            else { active_lsystem++; }

            lsystems.at(active_lsystem)->Draw_Generation(); // draw the active l-system

            SDL_RenderPresent(p_renderer); // present the render to the screen
            break;
        case 'c':
            if(active_lsystem != 100)
            {
                // change the colour of the currently selected l-system and redraw it
                lsystems.at(active_lsystem)->Change_Turtle_Colour();
                lsystems.at(active_lsystem)->Draw_Generation(); // draw the active l-system

                break;
            }
        case '1':
            iterations = 1;
            if(active_lsystem != 100)
            {
                // clear the current l-system, reprocess it with the correct iteration count and then draw it to the screen
                lsystems.at(active_lsystem)->Clear_Lsystem();
                lsystems.at(active_lsystem)->Process_Lsystem(iterations);
                lsystems.at(active_lsystem)->Draw_Generation(); // draw the active l-system
                
            }
            break;
        case '2':
            iterations = 2;
            if(active_lsystem != 100)
            {
                lsystems.at(active_lsystem)->Clear_Lsystem();
                lsystems.at(active_lsystem)->Process_Lsystem(iterations);
                lsystems.at(active_lsystem)->Draw_Generation(); // draw the active l-system
            }
            break;
        case '3':
            iterations = 3;
            if(active_lsystem != 100)
            {
                lsystems.at(active_lsystem)->Clear_Lsystem();
                lsystems.at(active_lsystem)->Process_Lsystem(iterations);
                lsystems.at(active_lsystem)->Draw_Generation(); // draw the active l-system
            }
            break;
        case '4':
            iterations = 4;
            if(active_lsystem != 100)
            {
                lsystems.at(active_lsystem)->Clear_Lsystem();
                lsystems.at(active_lsystem)->Process_Lsystem(iterations);
                lsystems.at(active_lsystem)->Draw_Generation(); // draw the active l-system
            }
            break;
        case '5':
            iterations = 5;
            if(active_lsystem != 100)
            {
                lsystems.at(active_lsystem)->Clear_Lsystem();
                lsystems.at(active_lsystem)->Process_Lsystem(iterations);
                lsystems.at(active_lsystem)->Draw_Generation(); // draw the active l-system
            }
            break;
        default:
            break;
        }
        SDL_RenderPresent(p_renderer); // present the render to the screen
    }
}
