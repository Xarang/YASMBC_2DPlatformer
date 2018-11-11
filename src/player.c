#include <math.h>
#include "player.h"
#include "time_utils.h"
#include "input.h"
#include "gamestate.h"
#include "audio.h"
#include "list.h"
#include "foe_1.h"
#include "block.h"

#define SIGN(X) (((X) > 0) - ((X) < 0))

//Reminder that the y axis is inverted

#define PLAYER_G_FORCE (-0.00001)
#define PLAYER_MAX_VEL 0.1
#define PLAYER_JUMP_ACC (-0.00025)
#define PLAYER_LATERAL_ACC 0.00001
#define PLAYER_RUN_FACTOR 2.0

#define PLAYER_LATERAL_AIR_FRICT_FACTOR (-0.0001)
#define PLAYER_LATERAL_GROUND_FRICT_FACTOR -0.0015
#define PLAYER_LATERAL_ICE_FRICT_FACTOR -0.00015
#define PLAYER_INERTIA_FACTOR (-0.002)
#define PLAYER_WALL_JUMP_X_FACTOR 0.005
#define PLAYER_WALL_JUMP_Y_FACTOR 0.009

#define PLAYER_JUMP_HOLD_ACC (-0.00001)
#define PLAYER_MAX_JUMP_FRAME 20

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

    if (inputs[JUMP])
    {
        if (player->is_grounded || player->is_walled)
        {
            play_sfx(SFX_JUMP, gamestate);
            if (player->is_grounded)
            {
                acc.y += PLAYER_JUMP_ACC;
            }
            else
            {
                float val = sqrt(2) / 2;
                player->transform.vel.x = val * PLAYER_WALL_JUMP_X_FACTOR *
                    -player->wall_dir;
                player->transform.vel.y = -val * PLAYER_WALL_JUMP_Y_FACTOR;
            }
        }
        else if (inputs[JUMP] < PLAYER_MAX_JUMP_FRAME)
        {
            acc.y += PLAYER_JUMP_HOLD_ACC;
        }
    }

    if (inputs[RUN])
    {
        acc.x *= PLAYER_RUN_FACTOR;
    }

    return acc;
}

static double get_frict_factor(enum block_type b_type)
{
    if (is_slippery(b_type))
    {
        return PLAYER_LATERAL_ICE_FRICT_FACTOR;
    }
    else
    {
        return PLAYER_LATERAL_GROUND_FRICT_FACTOR;
    }
}

static struct vector2 get_frict_acc(struct entity *player)
{
    struct vector2 frict;
    frict.y = 0;
    if (player->is_grounded)
    {
        frict.x = player->transform.vel.x *
                  get_frict_factor(player->ground_type);
    }
    else if (player->is_walled)
    {
        frict.y = 0;
    }
    else
    {
        frict.x = player->transform.vel.x * PLAYER_LATERAL_AIR_FRICT_FACTOR;
    }
    return frict;
}

static struct transform get_new_transform(struct entity *player,
                                          struct gamestate *gamestate)
{
    struct vector2 acc = { 0, -PLAYER_G_FORCE };
    acc = vector2_add(acc, get_move_acc(gamestate->inputs, gamestate), 1);
    acc = vector2_add(acc, get_frict_acc(player), 1);
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

static int collides_foes(struct entity *player, struct gamestate *gamestate)
{
    struct list *foes = gamestate->map->entities;
    struct entity *foe;
    size_t nb_entities = gamestate->map->nb_entities;
    for (size_t i = 0; i < nb_entities; i++)
    {
        foe = list_get_n(foes, i);
        if ((foe->type == FOE_1 || foe->type == BLOODY_FOE_1) &&
            collides_foe_1(player, foe))
        {
            foe->type = BLOODY_FOE_1;
            return 1;
        }
    }
    return 0;
}

enum entity_status update_player(struct entity *player,
                                 struct gamestate *gamestate)
{
    struct transform new_tf = get_new_transform(player, gamestate);
    struct transform old_tf = player->transform;

    //If the new vertical position is in a block
    enum block_type tile = map_get_type(gamestate->map, old_tf.pos.x,
                                        new_tf.pos.y);
    if (is_solid(tile))
    {
        //If the new vertical position is lower
        if (new_tf.pos.y >= old_tf.pos.y)
        {
            player->is_grounded = 1;
            player->ground_type = tile;
        }
        new_tf.vel.y = 0.0;
        new_tf.pos.y = old_tf.pos.y;
    }
    else if (is_deadly(tile))
    {
        kill_player(player, gamestate);
        return DIED;
    }
    else if (is_finish(tile))
    {
        return PLAYER_FINISH;
    }
    else
    {
        player->is_grounded = 0;
    }

    //If the new horizontal position is in a block
    tile = map_get_type(gamestate->map, new_tf.pos.x, old_tf.pos.y);
    if (is_solid(tile))
    {
        if (is_wall_jumpable(tile))
        {
            player->is_walled = 1;
            player->wall_dir = SIGN(new_tf.pos.x - old_tf.pos.x);
        }
        new_tf.vel.x = 0.0;
        new_tf.pos.x = old_tf.pos.x;
    }
    else if (is_deadly(tile))
    {
        kill_player(player, gamestate);
        return DIED;
    }
    else if (is_finish(tile))
    {
        return PLAYER_FINISH;
    }
    else
    {
        player->is_walled = 0;
    }
    player->transform = new_tf;

    if (collides_foes(player, gamestate))
    {
        kill_player(player, gamestate);
        return DIED;
    }
    return ALIVE;
}

void kill_player(struct entity *player, struct gamestate *gamestate)
{
    play_sfx(SFX_DEATH, gamestate);
    reset_entity(player);
    gamestate = gamestate;
}
