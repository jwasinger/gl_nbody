#ifndef RENDERER_H
#define RENDERER_H

#include "util.h"

namespace gl_nbody
{
    enum TRANSFORM_TYPE : UINT
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
        public:
            Renderer();
            ~Renderer();

            bool Init(SDL_window *mainWindow);
            void Render(void);

            void GetTriangleTransform() const;
            void
        private:
            void create_triangle(void);
            void render_triangle(void);
            void delete_triangle(void);

        private:
            SDL_window *main_window;
            SDL_GLContext gl_context_handle;
            GLUint program_id;
    };
}
#endif
