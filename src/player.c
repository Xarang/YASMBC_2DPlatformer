#include "player.h"
#include "time_utils.h"
#include "map.h"
#include "input.h"
#include "gamestate.h"

#define PLAYER_G_FORCE (-10)
#define PLAYER_MAX_VEL 0.1
#define PLAYER_LATERAL_ACC 10
#define PLAYER_RUN_FACTOR 1.3

static struct vector2 get_move_acc(int *inputs)
{
    struct vector2 acc = { 0, 0 };
    if (inputs[LEFT])
    {
        acc = vector2_add(acc, vector2_init(1, 0), -PLAYER_LATERAL_ACC);
    }
    if (inputs[RIGHT])
    {
        acc = vector2_add(acc, vector2_init(1, 0), PLAYER_LATERAL_ACC);
    }
    if (inputs[JUMP])
    {
        //Temporaire parce qu'il peut voler
        acc = vector2_add(acc, vector2_init(0, 1), -10);
    }
    if (inputs[RUN])
    {
        acc = vector2_scale(acc, PLAYER_RUN_FACTOR);
    }
    return acc;
}

static struct transform get_new_transform(struct entity *player,
                                          struct gamestate *gamestate)
{
    struct vector2 acc = { 0, -PLAYER_G_FORCE };
    acc = vector2_add(acc, get_move_acc(gamestate->inputs), 1);
    double delta = delta_time(&gamestate->last_update_time);

    struct transform tf = player->transform;
    tf.vel = vector2_add(tf.vel, acc, delta);
    double vel_norm = vector2_norm(tf.vel);
    if (vel_norm > PLAYER_MAX_VEL)
    {
        tf.vel = vector2_scale(tf.vel, PLAYER_MAX_VEL / vel_norm);
    }
    tf.pos = vector2_add(tf.pos, tf.vel, delta);
    return tf;
}

void update_player(struct entity *player, struct gamestate *gamestate)
{
    struct transform new_tf = get_new_transform(player, gamestate);
    struct transform old_tf = player->transform;

    //If the new vertical position is in a block
    if (map_get_type(gamestate->map, old_tf.pos.x, new_tf.pos.y) == BLOCK)
    {
        //If the new vertical position is lower
        if (new_tf.pos.y >= old_tf.pos.x)
        {
            player->is_grounded = 1;
        }
        new_tf.vel.y = 0.0;
        new_tf.pos.y = old_tf.pos.y;
    }
    //If the new horizontal position is in a block
    if (map_get_type(gamestate->map, new_tf.pos.x, old_tf.pos.y) == BLOCK)
    {
        new_tf.vel.x = 0.0;
        new_tf.pos.x = old_tf.pos.x;
    }
    player->transform = new_tf;
}
