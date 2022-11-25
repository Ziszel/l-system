#include "../include/sdl-app.hpp"
#include "../include/turtle.hpp"
#include "../include/l-system.hpp"
#include "../include/data-manager.hpp"
#include <vector>

using namespace sdl_helper;

// Branching tested with the axiom: FF[+F-F+F]F-F[F-F-F]+F[+FF-F[+F+F]F-F-F]F[-F[+F+F-F-F]F-F]
// located here: https://www.houdinikitchen.net/2019/12/21/how-to-create-l-systems/
// This works as expected, but other examples do not
// I believe my implementation does not handle edge re-writing nor nodes

int main()
{
    if (Init_SDL() < 0)
    {
        std::cout << "Error, SDL not initialised correctly\n";
        return -1;
    }

    // Create a new Data Manager object and load in ALL the configuration files
    Data_Manager dm;
    Lsystem_Data l_data_pa = dm.Load("rulesets/plant_a");
    Lsystem_Data l_data_pb = dm.Load("rulesets/plant_b");
    Lsystem_Data l_data_pc = dm.Load("rulesets/plant_c");
    Lsystem_Data l_data_pd = dm.Load("rulesets/plant_d");
    Lsystem_Data l_data_pe = dm.Load("rulesets/plant_e");
    Lsystem_Data l_data_pf = dm.Load("rulesets/plant_f");
    Lsystem_Data l_data_qs = dm.Load("rulesets/quadratic_snowflake");
    Lsystem_Data l_data_kce = dm.Load("rulesets/koch_curve_e");

    // Initialise objects
    // Created as pointer due to issue with implicit deletion when passed into
    // a vector
    Lsystem* lsystem_pa = new Lsystem(
        SCREEN_WIDTH / 2, // start x
        SCREEN_HEIGHT,    // start y
        &l_data_pa,
        p_renderer);
    Lsystem* lsystem_pb = new Lsystem(
        SCREEN_WIDTH / 2, // start x
        SCREEN_HEIGHT,    // start y
        &l_data_pb,
        p_renderer);
    Lsystem* lsystem_pc = new Lsystem(
        SCREEN_WIDTH / 2, // start x
        SCREEN_HEIGHT,    // start y
        &l_data_pc,
        p_renderer);
    Lsystem* lsystem_pd = new Lsystem(
        SCREEN_WIDTH / 2, // start x
        SCREEN_HEIGHT,    // start y
        &l_data_pd,
        p_renderer);
    Lsystem* lsystem_pe = new Lsystem(
        SCREEN_WIDTH / 2, // start x
        SCREEN_HEIGHT,    // start y
        &l_data_pe,
        p_renderer);
    Lsystem* lsystem_pf = new Lsystem(
        SCREEN_WIDTH / 2, // start x
        SCREEN_HEIGHT,    // start y
        &l_data_pf,
        p_renderer);
    Lsystem* lsystem_qs = new Lsystem(
        SCREEN_WIDTH / 2, // start x
        SCREEN_HEIGHT / 2,    // start y
        &l_data_qs,
        p_renderer);
    Lsystem* lsystem_kce = new Lsystem(
        SCREEN_WIDTH / 2, // start x
        SCREEN_HEIGHT / 2,    // start y
        &l_data_kce,
        p_renderer);

    // when passed into the Handle_Event() function as a non-pointer, encountered the following issue:
    // error: use of deleted function ‘Lsystem::Lsystem(const Lsystem&)’
    // Lsystem::Lsystem(const Lsystem&)’ is implicitly deleted because the default definition would be ill-formed:
    // Unable to fix, so passed in as pointers instead
    std::vector<Lsystem*> lsystems;

    lsystems.push_back(lsystem_pa);
    lsystems.push_back(lsystem_pb);
    lsystems.push_back(lsystem_pc);
    lsystems.push_back(lsystem_pd);
    lsystems.push_back(lsystem_pe);
    lsystems.push_back(lsystem_pf);
    lsystems.push_back(lsystem_qs);
    lsystems.push_back(lsystem_kce);

    // this ensures that something is viewable on the screen when the application first loads.
    // & passes by reference so that the values inside of lsystems are effected and not copies
    for(auto &ls : lsystems)
    {
        for (int i = 0; i <= iterations; ++i)
        {
            ls->Iterate_Generation();
        }
    }

    // Prepare event handling and enter main program loop
    SDL_Event event;

    while (program_running)
    {
        // Update
        // While there are events queued, process them
        while (SDL_PollEvent(&event) != 0)
        {
            Handle_Event(&event, lsystems);
        }

        // Draw
        // If there were moving imagery, I would draw it here.
        // However, I am handling the images simliar to a UI due to their static
        // nature. Therefore, they are handled through the 'Handle_Event() function
    }

    // CLEANUP
    // -------------------------------------------------------------------------

    // Destroy Window before closing SDL
    SDL_DestroyWindow(p_window);
    p_window = NULL; // Stop pointer referencing freed memory
    // Ensure SDL is quit before ending program
    SDL_Quit();

    // ensure data assigned to the heap is cleaned before exiting the program
    for (auto ls: lsystems)
    {
        delete(ls);
    }

    return 0;
}
