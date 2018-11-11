#ifndef UPDATE_H
#define UPDATE_H

#include "gamestate.h"

enum game_status
{
    RUNNING,
    WIN,
    GAME_ERROR
};

enum game_status update(struct gamestate *gamestate, int *inputs);

#endif /* ! UPDATE_H */
