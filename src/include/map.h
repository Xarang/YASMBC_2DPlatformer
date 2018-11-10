#ifndef MAP_H_
#define MAP_H_

#include <stddef.h>
#include "vector2.h"

enum block_type
{
    VOID  = 0,
    BLOCK = 1,
    FINISH= 2,
    DEATH = 3,
    ICE   = 4
};

struct map
{
    size_t width;
    size_t height;
    struct entity *entities;
    size_t nb_entities;
    enum block_type *blocks;
    struct vector2 start;
};
struct map *load_map(const char *filename);
enum block_type map_get_type(struct map *map, double i, double j);
void map_print(struct map *map);

#endif /*MAP_H_*/
