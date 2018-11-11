#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

enum entity_status update_player(struct entity *player,
                                struct gamestate *gamestate);
void kill_player(struct entity *player, struct gamestate *gamestate);

#endif /* ! PLAYER_H */
