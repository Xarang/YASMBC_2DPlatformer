#include "entity.h"
#include "player.h"
#include "foe_1.h"
#include "foe_2.h"

typedef void (*update_f)(struct entity *entity, struct gamestate *gamestate);

void update_entity(struct entity *entity, struct gamestate *gamestate)
{
    update_f f_list[NB_ENTITY_TYPE] =
    {
        update_player,
        update_foe_1,
        update_foe_2
    };
    f_list[entity->type](entity, gamestate);
}
