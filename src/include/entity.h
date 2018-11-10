#ifndef ENTITY_H
#define ENTITY_H

#include "vector2.h"
#include "gamestate.h"

#define NB_ENTITY_TYPE 3

enum entity_type
{
    PLAYER,
    FOE_1,
    FOE_2
};

struct transform
{
    double height;
    double width;
    struct vector2 pos;
    struct vector2 vel;
};

struct entity
{
    enum entity_type type;
    struct transform init_transform;
    struct transform transform;
    char is_grounded;
    char is_walled;
    char wall_dir;
    enum block_type ground_type;
    //SDL thingies
};

struct entity *create_entity(enum entity_type type, struct transform transform);
void reset_entity(struct entity *entity);
void destroy_entity(struct entity *entity);
void update_entity(struct entity *entity, struct gamestate *gamestate);
int collides(struct transform tf1, struct transform tf2);

#endif /* ! ENTITY_H */
