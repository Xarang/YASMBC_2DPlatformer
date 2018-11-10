#include "player.h"
#include "time_utils.h"

#define PLAYER_G_FORCE (-10)
#define PLAYER_MAX_VEL 0.01

static struct transform get_new_transform(struct entity *player,
                                          struct gamestate *gamestate)
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

void update_player(struct entity *player, struct gamestate *gamestate)
{
    struct transform new_tf = get_new_transform(player, gamestate);
    struct transform old_tf = player->transform;

    //If the new vertical position is in a block
    if (map_get_type(gamestate->map, old_tf.pos.x, new_tf.pos.y) == BLOCK)
    {
        //If the new vertical position is lower
        if (new_tf.pos.y >= old_tf.posx)
        {
            player->is_grounded = 1;
        }
        neW_tf.vel.y = 0.0;
        new_tf.pos.y = old_tf.pos.y;
    }
    //If the new horizontal position is in a block
    if (map_get_type(famestate->map, new_tf.pos.x, old_tf.y) == BLOCK)
    {
        new_tf.vel.x = 0.0;
        new_tf.pos.x = old_tf.pos.x;
    }
}
