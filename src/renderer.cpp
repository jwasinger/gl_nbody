#include "renderer.h"

namespace gl_nbody
{
    bool Renderer::Init(SDL_WINDOW *mainWindow)
    {
        if(!mainWindow)
            return false;

        this->mainWindow = mainWindow;

        //use Open GL 4.2
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

        this->mainContext = SDL_GL_CreateContext(window);
        if(!checkSDLError())
            return false;

        /* This makes our buffer swap syncronized with the monitor's vertical refresh */
        SDL_GL_SetSwapInterval(1);

        return true;
    }

    Renderer::Renderer(void) { }

    Renderer::~Renderer(void)
    {
        SDL_GL_DeleteContext(this->mainContext);
    }

    void Renderer::Render(void)
    {

}


    /* Clear our buffer with a red background */
    glClearColor ( 1.0, 0.0, 0.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    /* Swap our back buffer to the front */
    SDL_GL_SwapWindow(mainwindow);
}
