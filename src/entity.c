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
    switch (entity->type)
    {
    case PLAYER:
        return update_player(entity, gamestate);
    case FOE_1:
    case BLOODY_FOE_1:
        return update_foe_1(entity, gamestate);
    case FOE_2:
        return update_foe_2(entity, gamestate);
    };
    return ENTITY_ERROR;
}

void reset_entity(struct entity *entity)
{
    entity->transform = entity->init_transform;
    entity->is_grounded = 0;
    entity->is_walled = 0;
}

int collides_foe_disk(struct entity *player, struct entity *foe)
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
