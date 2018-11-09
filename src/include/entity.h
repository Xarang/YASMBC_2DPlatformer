#ifndef ENTITY_H
#define ENTITY_H

#include //input management
#include "vector2.h"

struct transform
{
    float height;
    float width;
    struct vector2 pos;
    struct vector2 vel;
};

struct entity
{
    struct transform transform;
    //SDL thingies
}

void move_player(struct entity *player, enum action action);

#endif /* ! ENTITY_H */
