#include <stdlib.h>
#include <stdio.h>
#include "entity.h"
#include "player.h"
#include "foe_1.h"
#include "foe_2.h"

typedef enum entity_status (*update_f)(struct entity *entity,
                                       struct gamestate *gamestate);

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
    res->is_walled = 0;
    res->state = 0;
    return res;
}

void print_transform(struct transform transform)
{
    printf("height : %f\n", transform.height);
    printf("width : %f\n", transform.width);
    printf("pos : %f/%f\n", transform.pos.x, transform.pos.y);
    printf("vel : %f/%f\n", transform.vel.x, transform.vel.y);

}

void print_entity(struct entity *entity)
{
    printf("entity of type %d\n", entity->type);
    printf("transform:\n");
    print_transform(entity->transform);
    printf("state : %d\n", entity->state);
}

void destroy_entity(struct entity *entity)
{
    free(entity);
}

enum entity_status update_entity(struct entity *entity, struct gamestate *gamestate)
{
    if (entity->type == PLAYER)
    {
        return update_player(entity, gamestate);
    }
    else if (entity->type == FOE_1 || entity->type == BLOODY_FOE_1)
    {
        return update_foe_1(entity, gamestate);
    }
    else if (entity->type == FOE_2)
    {
        return ENTITY_ERROR;
    }
    else
    {
        return ENTITY_ERROR;
    }
}

void reset_entity(struct entity *entity)
{
    entity->transform = entity->init_transform;
    entity->is_grounded = 0;
    entity->is_walled = 0;
}

#if 0
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
#endif
