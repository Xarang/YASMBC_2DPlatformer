#ifndef ENTITY_H
#define ENTITY_H

#include //input management
#include "vector2.h"

#define NB_ENTITY_TYPE 3

enum entity_type
{
    PLAYER,
    FOE_1,
    FOE_2
};

struct transform
{
    float height;
    float width;
    struct vector2 pos;
    struct vector2 vel;
};

struct entity
{
    enum entity_type type;
    struct transform transform;
    //SDL thingies
}

void update_entity(struct entity *entity, struct gamestate *gamestate);

#endif /* ! ENTITY_H */
