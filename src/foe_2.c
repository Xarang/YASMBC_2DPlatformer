#include "foe_2.h"
#include "time_utils.h"

static double get_mod(double x, double mod)
{
    while (x < 0)
    {
        x += mod;
    }
    while (x >= mod)
    {
        x -= mod;
    }
    return x;
}

enum entity_status update_foe_2(struct entity *foe, struct gamestate *gamestate)
{
    double delta = delta_time(&gamestate->last_update_time);
    struct transform tf = foe->transform;
    tf.pos = vector2_add(tf.pos, tf.vel, delta);
    tf.pos.x = get_mod(tf.pos.x, gamestate->map->width);
    tf.pos.y = get_mod(tf.pos.y, gamestate->map->height);
    foe->transform = tf;
    return ENTITY_ERROR;
}
