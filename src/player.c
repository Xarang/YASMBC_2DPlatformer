#include "player.h"
#include "time_utils.h"
#include "map.h"
#include "input.h"
#include "gamestate.h"
#include "audio.h"

//Reminder that the y axis is inverted

#define PLAYER_G_FORCE (-0.00001)
#define PLAYER_MAX_VEL 0.1
#define PLAYER_JUMP_ACC (-0.0004)
#define PLAYER_LATERAL_ACC 0.00001
#define PLAYER_RUN_FACTOR 2.0

#define PLAYER_LATERAL_AIR_FROT_FACTOR (-0.0001)
#define PLAYER_LATERAL_GROUND_FROT_FACTOR -0.0015
#define PLAYER_INERTIA_FACTOR (-0.002)

static struct vector2 get_move_acc(int *inputs, struct gamestate *gamestate)
{
    struct entity *player = gamestate->player;
    struct vector2 acc = { 0, 0 };
    if (inputs[LEFT])
    {
        acc = vector2_add(acc, vector2_init(1, 0), -PLAYER_LATERAL_ACC);
        if (!inputs[RIGHT] && player->transform.vel.x >= 0.0)
        {
            acc.x += player->transform.vel.x * PLAYER_INERTIA_FACTOR;
        }
    }
    if (inputs[RIGHT])
    {
        acc = vector2_add(acc, vector2_init(1, 0), PLAYER_LATERAL_ACC);
        if (!inputs[LEFT] && player->transform.vel.x <= 0.0)
        {
            acc.x += player->transform.vel.x * PLAYER_INERTIA_FACTOR;
        }
    }
    if (inputs[JUMP] && player->is_grounded)
    {
        Mix_PlayChannel(1, gamestate->sfxs[SFX_JUMP], 0);
        acc = vector2_add(acc, vector2_init(0, 1), PLAYER_JUMP_ACC);
    }
    if (inputs[RUN])
    {
        acc.x *= PLAYER_RUN_FACTOR;
    }
    return acc;
}

static struct vector2 get_frot_acc(struct entity *player,
                                   __attribute__((unused))struct gamestate *gamestate)
{
    struct vector2 frot;
    if (player->is_grounded)
    {
        frot.x = player->transform.vel.x * PLAYER_LATERAL_GROUND_FROT_FACTOR;
    }
    else
    {
        frot.x = player->transform.vel.x * PLAYER_LATERAL_AIR_FROT_FACTOR;
    }
    frot.y = 0;
    return frot;
}

static struct transform get_new_transform(struct entity *player,
                                          struct gamestate *gamestate)
{
    struct vector2 acc = { 0, -PLAYER_G_FORCE };
    acc = vector2_add(acc, get_move_acc(gamestate->inputs, gamestate), 1);
    acc = vector2_add(acc, get_frot_acc(player, gamestate), 1);
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
    printf("old: (%f, %f)\nnew: (%f, %f)\n\n", old_tf.pos.x, old_tf.pos.y,
           new_tf.pos.x, new_tf.pos.y);

    //If the new vertical position is in a block
    if (map_get_type(gamestate->map, old_tf.pos.x, new_tf.pos.y) == BLOCK)
    {
        //If the new vertical position is lower
        if (new_tf.pos.y >= old_tf.pos.y)
        {
            player->is_grounded = 1;
        }
        new_tf.vel.y = 0.0;
        new_tf.pos.y = old_tf.pos.y;
    }
    else
    {
        player->is_grounded = 0;
    }
    //If the new horizontal position is in a block
    if (map_get_type(gamestate->map, new_tf.pos.x, old_tf.pos.y) == BLOCK)
    {
        new_tf.vel.x = 0.0;
        new_tf.pos.x = old_tf.pos.x;
    }
    player->transform = new_tf;
}
