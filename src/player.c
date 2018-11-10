#include "player.h"
#include "time_utils.h"

#define PLAYER_G_FORCE (-10)
#define PLAYER_MAX_VEL 0.01

void update_player(struct entity *entity, struct gamestate *gamestate)
{
    struct vector2 acc = { 0, -PLAYER_G_FORCE };
    double delta = delta_time(&gamestate->last_update_time);

    struct transform tf = entity->transform;
    tf.vel = vector2_add(tf.vel, acc, delta);
    double vel_norm = vector2_norm(tf.vel);
    if (vel_norm > PLAYER_MAX_VEL)
    {
        tf.vel = vector2_scale(tf.vel, PLAYER_MAX_VEL / vel_norm);
    }
    tf.pos = vector2.add(tf.pos, tf.vel, delta);
}
