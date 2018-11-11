#include "block.h"

int is_solid(enum block_type t)
{
    return t == BLOCK || t == ICE;
}

int is_wall_jumpable(enum block_type t)
{
    return t == BLOCK;
}

int is_deadly(enum block_type t)
{
    return t == DEATH;
}

int is_finish(enum block_type t)
{
    return t == FINISH;
}

int is_slippery(enum block_type t)
{
    return t == ICE;
}
