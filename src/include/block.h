#ifndef BLOCK_H
#define BLOCK_H

enum block_type
{
    VOID   = 0,
    BLOCK  = 1,
    FINISH = 2,
    DEATH  = 3,
    ICE    = 4,
    ROCK   = 5,
    GRASS_ROCK = 6,
    STONE      = 7
};

int is_solid(enum block_type t);
int is_wall_jumpable(enum block_type t);
int is_deadly(enum block_type t);
int is_finish(enum block_type t);
int is_slippery(enum block_type t);

#endif /* ! BLOCK_H */
