#include "../include/sdl-app.hpp"
#include "../include/turtle.hpp"
#include "../include/l-system.hpp"

using namespace sdl_helper;

// Branching tested with the axiom: FF[+F-F+F]F-F[F-F-F]+F[+FF-F[+F+F]F-F-F]F[-F[+F+F-F-F]F-F]
// located here: https://www.houdinikitchen.net/2019/12/21/how-to-create-l-systems/
// This works as expected, but other examples do not
// I believe my implementation does not handle edge re-writing nor nodes

int main(int argc, char *args[])
{
    if (Init_SDL() < 0)
    {
        std::cout << "Error, SDL not initialised correctly\n";
        return -1;
    }

    int iterations = 3;

    // Initialise objects
    Lsystem lsystem(
        "F", // axiom
        SCREEN_WIDTH / 2, // start x
        SCREEN_HEIGHT, // start y
        255, // r
        0, // g
        0,  // b
        255, // a
        25.7f, // theta
        10.0f, // length
        p_renderer
    );

    for (int i = 0; i <= iterations; ++i)
    {
        lsystem.Iterate_Generation();
    }

    // handle one-time drawing outside of Draw loop
    SDL_SetRenderDrawColor(p_renderer, 0, 0, 0, 255);
    SDL_RenderClear(p_renderer);

    if (iterations > 0)
    {
        lsystem.Draw_Generation();
    }

    SDL_RenderPresent(p_renderer);

    // Prepare event handling and enter main program loop
    SDL_Event event;

    while (program_running)
    {
        // While there are events queued, process them
        while (SDL_PollEvent(&event) != 0)
        {
            Handle_Event(&event);
        }

        // Update

        // Draw
    }

    // CLEANUP
    // -------------------------------------------------------------------------

    // Destroy Window before closing SDL
    SDL_DestroyWindow(p_window);
    p_window = NULL; // Stop pointer referencing freed memory
    // Ensure SDL is quit before ending program
    SDL_Quit();

    return 0;
}
