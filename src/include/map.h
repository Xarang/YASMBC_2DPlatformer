#ifndef MAP_H_
#define MAP_H_

#include "game.h"


enum block_type
{
    VOID  = 0,
    BLOCK = 1,
    FINISH= 2
};

struct map
{
    size_t width;
    size_t height;
    enum block_type *blocks;
    struct vector2 start;
};
struct map *load_map(const char *filename);
enum block_type map_get_type(struct map *map, size_t i, size_t j);
void map_print(struct map *map);

#endif /*MAP_H_*/
