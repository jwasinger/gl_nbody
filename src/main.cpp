#include <iostream>
#include "renderer.h"
#include <SDL2/SDL.h>
#include <GL/gl.h>
SDL_window *mainWindow = nullptr;
InputController *inputController = nullptr;
Renderer *renderer = nullptr;
Simulation *simulation = nullptr;
bool debugTerminalRunning = false;
bool useDebugTerminal = true;

int main(int argc, char *argv[]);
bool init(void);
void render(void);
void update(void);
void freeAppResources(void);

int main(int argc, char *argv[])
{
    /*****************************************************************************
    /   Init routine:
    /   1) create window
    /   2) create debug terminal
    /   2) create input controller
    /   3) create renderer
    /   4) initiallize simulation
    /******************************************************************************/

    /* Create our window centered at 512x512 resolution */
    mainwindow = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!mainwindow) /* Die if creation failed */
        std::cout << "\nSDL_CreateWindow() failed\n"

    //create debug terminal

    //create input controller

    //create renderer
    renderer = new Renderer();
    //initiallize simulation

    while(true)
    {
        //process events in the queue
        //if quit event, quit out
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {

        }

        //render(),update()
        renderer->render();
    }

    delete renderer;
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();
    return 0;
}
