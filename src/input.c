#include <stddef.h>
#include <SDL.h>
#include "input.h"

static void reset_array(enum action inputs[NB_ACTION])
{
    for (size_t i = 0; i < NB_ACTION; i++)
        inputs[i] = 0;
}

void get_input(enum action inputs[NB_ACTION])
{
    reset_array(inputs);
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT])
        inputs[LEFT]++;
    if (state[SDL_SCANCODE_RIGHT])
        inputs[RIGHT]++;
    if (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_UP])
        inputs[JUMP]++;
    if (state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT])
        inputs[RUN]++;
    if (state[SDL_SCANCODE_ESCAPE])
        inputs[PAUSE]++;
    if (state[SDL_SCANCODE_R])
        inputs[RESTART]++;
}
