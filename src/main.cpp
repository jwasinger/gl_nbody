#include <iostream>
#include <SDL2/SDL.h>

#include "glew.h"
#include <GL/gl.h>

#include "Renderer.h"
#include "InputController.h"

//#include "Simulation.h"

SDL_Window *main_window = NULL;
//InputController *inputController = nullptr;
gl_nbody::Renderer *renderer = nullptr;
//Simulation *simulation = nullptr;
bool debugTerminalRunning = false;
bool useDebugTerminal = true;

bool init(void);
void render(void);
void update(void);
void freeAppResources(void);

int main(void)
{
	std::cout << "hello world!";

    SDL_Init(SDL_INIT_VIDEO);

    /*****************************************************************************
    /   Init routine:
    /   1) create window
    /   2) create debug terminal
    /   2) create input controller
    /   3) create renderer
    /   4) initiallize simulation
    /******************************************************************************/

    /* Create our window centered at 512x512 resolution */
    main_window = SDL_CreateWindow("PROGRAM_NAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!main_window) /* Die if creation failed */
        std::cout << "\nSDL_CreateWindow() failed\n";

    //create debug terminal

    //create input controller

    //create renderer
    renderer = new gl_nbody::Renderer();
    if(!renderer->Init(main_window))
    {
        std::cout << glewGetErrorString(GLEW_VERSION);
    }

    //initiallize simulation

    bool quit = false;

    while(true)
    {
        if(quit)
            break;

        //process events in the queue
        //if quit event, quit out
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
             //do something, for now no controls
        }

        renderer->Render();
        //render(),update()

    }

    //delete renderer;
    //SDL_DestroyWindow(main_window);
    //SDL_Quit();
    return 0;
}
