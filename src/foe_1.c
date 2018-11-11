#include <stdlib.h>
#include "foe_1.h"
#include "map.h"
#include "time_utils.h"

enum entity_status update_foe_1(struct entity *foe, struct gamestate *gamestate)
{
    double delta = delta_time(&gamestate->last_update_time);
    struct transform old_tf = foe->transform;
    struct transform new_tf = old_tf;
    new_tf.pos = vector2_add(new_tf.pos, new_tf.vel, delta);
    enum block_type tile_lateral = map_get_type(gamestate->map, old_tf.pos.x,
                                                new_tf.pos.y);
    enum block_type tile_vertical = map_get_type(gamestate->map, new_tf.pos.x,
                                                old_tf.pos.y);
    if (tile_lateral != VOID || tile_vertical != VOID)
    {
        new_tf = old_tf;
        new_tf.vel = vector2_scale(new_tf.vel, -1);
    }
    return ENTITY_ERROR;
}

//Foe_1 has the form of a disk

int collides_foe_1(struct entity *player, struct entity *foe)
{
    struct transform p_tf = player->transform;
    double radius = foe->transform.width / 2;
    struct vector2 center = foe->transform.pos;
    struct vector2 corner = p_tf.pos;
    corner.x -= p_tf.width / 2.0;
    corner.y -= p_tf.height / 2.0;

    //Top left corner
    if (vector2_norm(vector2_add(corner, center, -1)) <= radius)
    {
        return 1;
    }

    corner.x += p_tf.width;
    //Top right corner
    if (vector2_norm(vector2_add(corner, center, -1)) <= radius)
    {
        return 1;
    }

    corner.y += p_tf.height;
    //Bottom right corner
    if (vector2_norm(vector2_add(corner, center, -1)) <= radius)
    {
        return 1;
    }

    corner.x -= p_tf.width;
    //Bottom left corner
    if (vector2_norm(vector2_add(corner, center, -1)) <= radius)
    {
        return 1;
    }
    return 0;
}
