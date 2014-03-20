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

        private:
            void createTriangle(void);
            void renderTriangle(void);
            void deleteTriangle(void);

        private:
            SDL_window *mainWindow;
            SDL_GLContext glContextHandle;
    };
}
#endif
