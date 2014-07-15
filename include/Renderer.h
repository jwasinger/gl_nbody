#ifndef RENDERER_H
#define RENDERER_H

#include "Util.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/gl.h>

namespace gl_nbody
{
    enum TRANSFORM_TYPE
    {
        TRANSFORM_WORLD,
        TRANSFORM_PROJECTION,
        TRANSFORM_VIEW,
    };

    enum SHADER_TYPE
    {
        SHADER_TYPE_NONE = 0,
        SHADER_TYPE_COLOR,
        SHADER_TYPE_POINT_SPRITE,
        SHADER_TYPE_TEXTURE,
    };

    class Renderer
    {
        private:
            void create_triangle(void);
            void render_triangle(void);
            void delete_triangle(void);
            bool load_shaders(void);

        private:
            SDL_Window *main_window;
            SDL_GLContext gl_context;
            GLuint program;
            GLuint tri_buffer;
            GLuint vertex_shader, frag_shader;

        public:
            Renderer();
            ~Renderer();

            bool Init(SDL_Window **mainWindow);
            void Render(void);

            void GetTriangleTransform() const;
    };
}
#endif
