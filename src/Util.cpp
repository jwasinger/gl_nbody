#include "Util.h"

#include <SDL2/SDL.h>
#include <cstdio>

bool SDLError(void)
{
    const char *error = SDL_GetError();
    if (*error != '\0')
    {
        printf("SDL Error: %s\n", error);
        printf(" + line: %i\n", __LINE__);
        SDL_ClearError();
        return true;
    }
}
