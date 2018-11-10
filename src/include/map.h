#ifndef MAP_H_
#define MAP_H_

#include "game.h"

struct map
{
    size_t width;
    size_t height;
    char *blocks;
    struct vector2 start;
};

enum block_type
{
    VOID,
    BLOCK,
    FINISH
};

struct map *load_map(const char *filename);
enum block_type map_get_type(struct map *map, size_t i, size_t j);


#endif /*MAP_H_*/
