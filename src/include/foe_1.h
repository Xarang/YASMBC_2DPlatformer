#ifndef FOE_1_H
#define FOE_1_H

#include "entity.h"

enum entity_status update_foe_1(struct entity *foe,
                                struct gamestate *gamestate);
int collides_foe_1(struct entity *player, struct entity *foe);

#endif /* ! FOE_1_H */
