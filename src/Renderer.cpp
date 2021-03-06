#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>

/* If using gl3.h */
/* Ensure we are using opengl's core profile only */
#include "glew.h"
#define GL3_PROTOTYPES 1
#include <GL/gl.h>

#include "SDL2/SDL.h"
#include "Renderer.h"

namespace gl_nbody
{
    bool Renderer::Init(SDL_Window **main_window)
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

        *main_window = SDL_CreateWindow("PROGRAM_NAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

        if (!main_window) /* Die if creation failed */
            std::cout << "\nSDL_CreateWindow() failed\n";

        this->main_window = *main_window;

        //use Open GL 3.1

        this->gl_context = SDL_GL_CreateContext(this->main_window);
        if(SDLError())
            return false;

        //

        // Init GLEW -------------------------------------------------------------------
        GLenum err = glewInit();
        if(err != GLEW_OK)
        {
            std::cout << "Error initiallizing GLEW" << std::endl;
            return false;
        }

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
        glDeleteShader(this->vertex_shader);
        glDeleteShader(this->frag_shader);
        glDeleteProgram(this->program);
    }

    void Renderer::create_triangle()
    {
        float verts[] =
        {
            0.0f, 1.0f, 0.5f, 1.0f,
            1.0f, 1.0f, 0.5f, 1.0f,
            0.0f, 0.0f, 0.5f, 1.0f,
        };

        glGenBuffers(1, &this->tri_buffer);

        glBindBuffer(GL_ARRAY_BUFFER, this->tri_buffer);
        glBufferData(this->tri_buffer, sizeof(float) * 12, verts, GL_STATIC_DRAW);
    }

    void Renderer::delete_triangle()
    {}

    void Renderer::render_triangle()
    {
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, this->tri_buffer); //is this line needed?
        glVertexAttribPointer(this->tri_buffer,
                              3,
                              GL_FLOAT,
                              GL_FALSE,
                              0,
                              (void *)0
                              );

        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableVertexAttribArray(1);
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

    int load_shader(char* filename, GLchar** ShaderSource, int& len)
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

        (*ShaderSource)[len] = '\0';

        // read data as a block:
        file.read(*ShaderSource,len);

        file.close();

        // len isn't always strlen cause some characters are stripped in ascii read...
        // it is important to 0-terminate the real length later, len is just max possible value...
//        *ShaderSource[len] = 0;
//
//        unsigned int i=0;
//        while (file.good())
//        {
//            *ShaderSource[i] = file.get();       // get character from file.
//            if (!file.eof())
//                i++;
//        }

//        *ShaderSource[i] = 0;  // 0-terminate it at the correct position

//        file.close();

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

    void log_shader_linker_errors(GLuint program)
    {
        GLint is_linked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &is_linked);
        if(is_linked == GL_FALSE)
        {
            GLint max_length = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_length);

            //The maxLength includes the NULL character
            std::vector<GLchar> infoLog(max_length);
            glGetProgramInfoLog(program, max_length, &max_length, &infoLog[0]);

            for(std::vector<GLchar>::const_iterator i = infoLog.begin(); i != infoLog.end(); ++i)
                std::cout << *i;

            std::cout << std::endl;

            //Provide the infolog in whatever manor you deem best.
            //Exit with failure.
            return;
        }
    }

    void log_shader_compiler_errors(GLuint shader_object)
    {
        GLint max_len = 0;

        glGetShaderiv(shader_object, GL_INFO_LOG_LENGTH , &max_len);
        if (max_len > 1)
        {
            std::vector<GLchar> infoLog(max_len);
            glGetShaderInfoLog(shader_object, max_len, &max_len, &infoLog[0]);

            for(std::vector<GLchar>::const_iterator i = infoLog.begin(); i != infoLog.end(); ++i)
                std::cout << *i;

            std::cout << std::endl;
        }
    }

    bool Renderer::load_shaders(void)
    {
        this->vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        this->frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

        //load shader source code from files

        int vLength, fLength;
        GLchar *vSource = nullptr;
        GLchar *fSource = nullptr;

        int error = 0;
        error = load_shader("shaders/basic.frag", &fSource, fLength);
        log_shader_load_error(error);
        if(error != 0)
            return false;

        error = load_shader("shaders/basic.vert", &vSource, vLength);
        log_shader_load_error(error);
        if(error != 0)
            return false;

        //attach and compile shaders
        const GLchar *v_src = (const GLchar *)vSource;
        glShaderSource(this->vertex_shader, 1, &v_src, NULL);

        const GLchar *f_src = (const GLchar *)fSource;
        glShaderSource(this->frag_shader, 1, &f_src, NULL);
        //this is ugly ^^ change it soon

        glCompileShader(this->vertex_shader);
        glCompileShader(this->frag_shader);

        GLint compiled;
        //glGetObjectParameterivARB(this->vertex_shader, GL_COMPILE_STATUS, &compiled);
        glGetShaderiv(this->vertex_shader, GL_COMPILE_STATUS, &compiled);
        if(!compiled)
        {

            std::cout << "Error: compilation of vertex shader failed."
                      << std::endl
                      << "Compiler log: "
                      << std::endl;

            log_shader_compiler_errors(this->vertex_shader);
            return false;
        }

        glGetShaderiv(this->frag_shader, GL_COMPILE_STATUS, &compiled);
        if(!compiled)
        {
            std::cout << "Error: compilation of fragment shader failed."
                      << std::endl
                      << "Compiler log: "
                      << std::endl;

            log_shader_compiler_errors(this->frag_shader);
            return false;
        }

        glAttachShader(this->program, this->vertex_shader);
        glAttachShader(this->program, this->frag_shader);
        glLinkProgram(this->program);

        GLint linked;
        glGetProgramiv(this->program, GL_LINK_STATUS, &linked);
        if(!linked)
        {
            log_shader_linker_errors(this->program);

            return false;
        }

        return true;
    }
}
