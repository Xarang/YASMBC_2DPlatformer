#ifndef INPUT_H
# define INPUT_H

#include "gamestate.h"

#define NB_ACTION 7

enum action
{
    LEFT,
    RIGHT,
    JUMP,
    RUN,
    PAUSE,
    EXIT,
    RESTART
};

void get_input(int *inputs, struct gamestate *game);

#endif /* ! INPUT_H */
