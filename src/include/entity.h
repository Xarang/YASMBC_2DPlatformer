#ifndef ENTITY_H
#define ENTITY_H

#include "vector2.h"
#include "gamestate.h"

#define NB_ENTITY_TYPE 3

enum entity_status
{
    ALIVE,
    DIED,
    PLAYER_FINISH,
    ENTITY_ERROR
};

enum entity_type
{
    PLAYER = 0,
    FOE_1  = 1,
    FOE_2  = 2,
    BLOODY_FOE_1 = 10
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
    int state;
};

struct entity *create_entity(enum entity_type type, struct transform transform);
void reset_entity(struct entity *entity);
void destroy_entity(struct entity *entity);
enum entity_status update_entity(struct entity *entity,
                                 struct gamestate *gamestate);
int collides_foe_disk(struct entity *player, struct entity *foe);
void print_entity(struct entity *entity);

#endif /* ! ENTITY_H */
