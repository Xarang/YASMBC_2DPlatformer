#include <SDL.h>
//#include "time_utils.h"

double delta_time(uint64_t *last_update_time)
{
    double frequency = SDL_GetPerformanceFrequency();

    uint64_t last = *last_update_time;
    uint64_t now = SDL_GetPerformanceCounter();

    *last_update_time = now;

    double delta = (now - last) * 1000 / frequency;
    printf("Delta = %f\n", delta);
    return delta;
}
