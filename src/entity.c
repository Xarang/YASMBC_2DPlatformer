#include <stdlib.h>
#include <stdio.h>
#include "entity.h"
#include "player.h"
#include "foe_1.h"
#include "foe_2.h"

typedef void (*update_f)(struct entity *entity, struct gamestate *gamestate);

struct entity *create_entity(enum entity_type type, struct transform transform)
{
    struct entity *res = malloc(sizeof(struct entity));
    if (!res)
    {
        fprintf(stderr, "Failed to malloc(sizeof(struct entity))\n");
        return NULL;
    }
    res->type = type;
    res->transform = transform;
    res->init_transform = transform;
    res->is_grounded = 0;
    return res;
}

void destroy_entity(struct entity *entity)
{
    free(entity);
}

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

static int is_in_hitbox(struct vector2 point, struct transform tf)
{
    struct vector2 center = tf.pos;
    double semi_w = tf.width / 2.0;
    double semi_h = tf.height / 2.0;
    return center.x - semi_w <= point.x &&
           point.x <= center.x + semi_w &&
           center.y - semi_h <= point.y &&
           point.y <= center.y + semi_h;
}

int collides(struct transform tf1, struct transform tf2)
{
    struct vector2 corner = tf1.pos;
    corner.x -= tf1.width / 2.0;
    corner.y -= tf1.height / 2.0;

    //Top left corner
    if (is_in_hitbox(corner, tf2))
    {
        return 1;
    }

    corner.x += tf1.width;
    //Top right corner
    if (is_in_hitbox(corner, tf2))
    {
        return 1;
    }

    corner.y += tf1.height;
    //Bottom right corner
    if (is_in_hitbox(corner, tf2))
    {
        return 1;
    }

    corner.x -= tf1.width;
    //Bottom left corner
    if (is_in_hitbox(corner, tf2))
    {
        return 1;
    }
    return 0;
}
