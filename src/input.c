#include <stddef.h>
#include <SDL.h>
#include "input.h"

static void reset_array(int *inputs)
{
    for (size_t i = 0; i < NB_ACTION; i++)
        inputs[i] = 0;
}

void get_input(int *inputs, struct gamestate *game)
{
    int jump_val = inputs[JUMP];
    int pause_val = inputs[PAUSE];
    int restart_val = inputs[RESTART];

    reset_array(inputs);
    SDL_PumpEvents();
    const Uint8 *state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_LEFT])
        inputs[LEFT]++;
    if (state[SDL_SCANCODE_RIGHT])
        inputs[RIGHT]++;
    if (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_UP])
    {
        if (jump_val)
            inputs[JUMP] = jump_val;
        inputs[JUMP]++;
    }
    if (state[SDL_SCANCODE_LSHIFT] || state[SDL_SCANCODE_RSHIFT])
        inputs[RUN]++;
    if (state[SDL_SCANCODE_P])
    {
        if (pause_val)
            inputs[PAUSE] = pause_val;
        inputs[PAUSE]++;
    }
    if (state[SDL_SCANCODE_ESCAPE])
        inputs[EXIT]++;
    if (state[SDL_SCANCODE_R])
        if (restart_val)
            inputs[RESTART] = restart_val;
        inputs[RESTART]++;
    game->inputs = inputs;
}
