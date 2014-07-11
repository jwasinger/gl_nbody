#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

/* If using gl3.h */
/* Ensure we are using opengl's core profile only */
#include "glew.h"
#define GL3_PROTOTYPES 1
#include <GL/gl.h>

#include "SDL2/SDL.h"
#include "Renderer.h"

namespace gl_nbody
{
    bool Renderer::Init(SDL_Window *mainWindow)
    {
        if(!mainWindow)
            return false;

        this->main_window = mainWindow;

        //use Open GL 4.2
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

        this->gl_context = SDL_GL_CreateContext(this->main_window);
        if(!checkSDLError())
            return false;

        this->program = glCreateProgram();

        /* This makes our buffer swap syncronized with the monitor's vertical refresh */
        SDL_GL_SetSwapInterval(1);

        if(!this->load_shaders())
            return false;

        return true;
    }

    Renderer::Renderer(void) { }

    Renderer::~Renderer(void)
    {
        SDL_GL_DeleteContext(this->gl_context);
    }

    void Renderer::create_triangle()
    {
        float verts[] =
        {
            0.0f, 1.0f, 0.5f,
            1.0f, 1.0f, 0.5f,
            0.0f, 0.0f, 0.5f,
        };

        glGenBuffers(1, &this->tri_buffer);

        glBindBuffer(GL_ARRAY_BUFFER, this->tri_buffer);
        glBufferData(this->tri_buffer, sizeof(float) * 9, verts, GL_STATIC_DRAW);
    }

    void Renderer::delete_triangle()
    {}

    void Renderer::render_triangle()
    {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, this->tri_buffer); //is this line needed?
        glVertexAttribPointer(this->tri_buffer,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void *)0
                              );

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(0);
    }

    void Renderer::Render(void)
    {
        glClearColor ( 0.0, 0.0, 1.0, 1.0 );
        glClear ( GL_COLOR_BUFFER_BIT );

        this->render_triangle();

        SDL_GL_SwapWindow(this->main_window);
    }

    enum
    {
        SUCCESS = 0,
        FILE_NOT_FOUND,
        EMPTY_FILE,
        OUT_OF_MEMORY,
    };

    unsigned long get_file_length(std::ifstream& file)
    {
        if(!file.good())
            return 0;

        unsigned long pos=file.tellg();
        file.seekg(0,std::ios::end);
        unsigned long len = file.tellg();
        file.seekg(std::ios::beg);

        return len;
    }

    int load_shader(char* filename, GLchar** ShaderSource, unsigned long& len)
    {
        std::ifstream file;
        file.open(filename, std::ios::in); // opens as ASCII!
        if(!file)
            return FILE_NOT_FOUND;

        len = get_file_length(file);

        if (len==0)
            return EMPTY_FILE;   // Error: Empty File

        *ShaderSource = new char[len+1];
        if (*ShaderSource == 0)
            return OUT_OF_MEMORY;   // can't reserve memory

        // len isn't always strlen cause some characters are stripped in ascii read...
        // it is important to 0-terminate the real length later, len is just max possible value...
        *ShaderSource[len] = 0;

        unsigned int i=0;
        while (file.good())
        {
            *ShaderSource[i] = file.get();       // get character from file.
            if (!file.eof())
                i++;
        }

        *ShaderSource[i] = 0;  // 0-terminate it at the correct position

        file.close();

        return SUCCESS; // No Error
    }


    int unload_shader(GLubyte** ShaderSource)
    {
        if (*ShaderSource != 0)
            delete[] *ShaderSource;
        *ShaderSource = 0;
    }

    void log_shader_load_error(int error)
    {
        //for now just use cout
        switch(error)
        {
            case SUCCESS:
                break;

            case FILE_NOT_FOUND:
                std::cout << "Error: File not found!" << std::endl;
                break;

            case EMPTY_FILE:
                std::cout << "Error: Empty file!" << std::endl;
                break;

            case OUT_OF_MEMORY:
                std::cout << "Error: Out of memory!" << std::endl;
                break;

            default:
                std::cout << "Error: Unknown error" << std::endl;
        }
    }

    void log_shader_compiler_errors(GLuint shader_object)
    {
        GLint blen = 0;
        GLsizei slen = 0;

        glGetShaderiv(shader_object, GL_INFO_LOG_LENGTH , &blen);
        if (blen > 1)
        {
            GLchar* compiler_log = (GLchar*)malloc(blen);
            glGetInfoLogARB(shader_object, blen, &slen, compiler_log);
            std::cout << compiler_log << std::endl;
            free(compiler_log);
        }
    }

    bool Renderer::load_shaders(void)
    {
        this->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        this->frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

        //load shader source code from files

        unsigned long vLength, fLength;
        GLchar **vSource = nullptr;
        GLchar **fSource = nullptr;

        int error = 0;
        error = load_shader("shaders/basic.frag", fSource, fLength);
        log_shader_load_error(error);
        if(error != 0)
            return false;

        error = load_shader("shaders/basic.vert", vSource, vLength);
        log_shader_load_error(error);
        if(error != 0)
            return false;

        //attach and compile shaders

        glShaderSourceARB(this->vertex_shader, 1, (const char **)vSource, &vLength);
        glShaderSourceARB(this->frag_shader, 1, (const char **)fSource, &fLength);

        glCompileShaderARB(this->vertex_Shader);
        glCompileShaderARB(this->frag_shader);

        GLint compiled;
        glGetObjectParameteriv(this->vertex_shader, GL_COMPILE_STATUS, &compiled);
        if(!compiled)
        {

            std::cout << "Error: compilation of vertex shader failed."
                      << std::endl
                      << "Compiler log: "
                      << std::endl;

            log_shader_compiler_errors(this->vertex_shader);
            return false;
        }

        glGetObjectParameteriv(this->frag_shader, GL_COMPILE_STATUS, &compiled);
        if(!compiled)
        {
            std::cout << "Error: compilation of fragment shader failed."
                      << std::endl
                      << "Compiler log: "
                      << std::endl;

            log_shader_compiler_errors(this->vertex_shader);
            return false;
        }

        glAttachShader(this->program, this->vertex_shader);
        glAttachShader(this->program, this->frag_shader);
        glLinkProgram(this->program);

        GLint linked;
        glGetProgramiv(this->program, GL_LINK_STATUS, &linked);
        if(!linked)
        {
            std::cout << "Error: Shader linking failed!" << std::endl;
            //TODO: output the exact nature of the linking error
            //http://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/loading.php

            return false;
        }

        return true;
    }

    //random rendering-related code from SDL 2.0 sample
    {
        /* A simple function that prints a message, the error code returned by SDL,
         * and quits the application */
        void sdldie(const char *msg)
        {
            printf("%s: %s\n", msg, SDL_GetError());
            SDL_Quit();
            exit(1);
        }


        void checkSDLError(int line = -1)
        {
        #ifndef NDEBUG
            const char *error = SDL_GetError();
            if (*error != '\0')
            {
                printf("SDL Error: %s\n", error);
                if (line != -1)
                    printf(" + line: %i\n", line);
                SDL_ClearError();
            }
        #endif
        }

        bool loadShaders(char vertex[256], char frag[256])
        {
            if(!vertex || !frag)
            {
                return false;
            }


        }

        unsigned int vbo = 0;
        void createTriangle(void)
        {
            float points[] =
            {
                0.0f,  0.5f,  0.0f,
                0.5f, -0.5f,  0.0f,
               -0.5f, -0.5f,  0.0f
            };

            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points, GL_STATIC_DRAW);
        }

        /* Our program's entry point */
        int main(int argc, char *argv[])
        {
            SDL_Window *mainwindow; /* Our window handle */
            SDL_GLContext maincontext; /* Our opengl context handle */

            if (SDL_Init(SDL_INIT_VIDEO) < 0) /* Initialize SDL's Video subsystem */
                sdldie("Unable to initialize SDL"); /* Or die on error */

                /* Request opengl 3.2 context.
             * SDL doesn't have the ability to choose which profile at this time of writing,
                  * but it should default to the core profile */
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

            /* Turn on double buffering with a 24bit Z buffer.
                 * You may need to change this to 16 or 32 for your system */
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

            /* Create our window centered at 512x512 resolution */
            mainwindow = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
            if (!mainwindow) /* Die if creation failed */
                sdldie("Unable to create window");

            checkSDLError(__LINE__);

            /* Create our opengl context and attach it to our window */
            maincontext = SDL_GL_CreateContext(mainwindow);
            checkSDLError(__LINE__);


            /* This makes our buffer swap syncronized with the monitor's vertical refresh */
            SDL_GL_SetSwapInterval(1);

            /* Clear our buffer with a red background */
            glClearColor ( 1.0, 0.0, 0.0, 1.0 );
            glClear ( GL_COLOR_BUFFER_BIT );
            /* Swap our back buffer to the front */
            SDL_GL_SwapWindow(mainwindow);
            /* Wait 2 seconds */
            SDL_Delay(2000);

            /* Same as above, but green */
            glClearColor ( 0.0, 1.0, 0.0, 1.0 );
            glClear ( GL_COLOR_BUFFER_BIT );
            SDL_GL_SwapWindow(mainwindow);
            SDL_Delay(2000);

            /* Same as above, but blue */
            glClearColor ( 0.0, 0.0, 1.0, 1.0 );
            glClear ( GL_COLOR_BUFFER_BIT );
            SDL_GL_SwapWindow(mainwindow);
            SDL_Delay(2000);

            /* Delete our opengl context, destroy our window, and shutdown SDL */
            SDL_GL_DeleteContext(maincontext);
            SDL_DestroyWindow(mainwindow);
            SDL_Quit();

            return 0;
        }
        }
    }
}
