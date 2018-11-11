#ifndef FOE_1_H
#define FOE_1_H

#include "entity.h"

#define FOE_1_X_VEL 0.001
#define FOE_1_Y_VEL 0.0

enum entity_status update_foe_1(struct entity *foe,
                                struct gamestate *gamestate);

#endif /* ! FOE_1_H */
