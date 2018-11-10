#ifndef INPUT_H
# define INPUT_H

#include "gamestate.h"

#define NB_ACTION 6

enum action
{
    LEFT,
    RIGHT,
    JUMP,
    RUN,
    PAUSE,
    RESTART
};

void get_input(int *inputs, struct gamestate *game);

#endif /* ! INPUT_H */
