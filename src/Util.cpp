#include "Util.h"

#include <SDL2/SDL.h>
#include <cstdio>

bool checkSDLError(void);
{
    const char *error = SDL_GetError();
    if (*error != '\0')
    {
        printf("SDL Error: %s\n", error);
        if (line != -1)
            printf(" + line: %i\n", line);
        SDL_ClearError();
        return true;
    }
}