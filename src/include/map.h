#ifndef MAP_H_
#define MAP_H_

struct map
{
    size_t width;
    size_t height;
    char *blocks;
    struct vector2 start;
}

enum block_type
{
    VOID,
    BLOCK,
    FINISH
};

struct map *load_map(const char *filename);

#endif /*MAP_H_*/
