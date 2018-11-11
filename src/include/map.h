#ifndef MAP_H_
#define MAP_H_

#include <stddef.h>
#include "vector2.h"
#include "block.h"

struct map
{
    int world_id;
    size_t width;
    size_t height;
    struct list *entities;
    size_t nb_entities;
    enum block_type *blocks;
    struct vector2 start;
};
struct map *load_map(const char *filename);
enum block_type map_get_type(struct map *map, double i, double j);
void map_print(struct map *map);

#endif /*MAP_H_*/
