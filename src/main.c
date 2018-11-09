#include <SDL.h>

int main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        return 1;

    SDL_Quit();
    return 0;
}
