#include "game.h"

enum block_type type_from_char(char c)
{
    switch (c)
    {
        case '.':
            return VOID;
        case '#':
            return BLOCK;
        case 'F':
            return FINISH;
        case 'X':
            return DEATH;
        case '$':
            return ICE;
        default :
            return VOID;
    }
}

char char_from_type(enum block_type type)
{
    switch(type)
    {
        case VOID:
            return '.';
        case BLOCK:
            return '#';
        case FINISH:
            return 'F';
        case DEATH:
            return 'X';
        case ICE:
            return '$';
    }
    return '.';
}

void parse_entities(FILE *f, struct map *map, int n)
{
    char **ptr = malloc(sizeof(char*));
    *ptr = NULL;
    int parsing_entity = 0;
    size_t a = 64;
    struct entity *entities = malloc(sizeof(struct entity) * n);
    while (n >= 0)
    {
        int try = getline(ptr, &a, f);
        *(*ptr + try - 1) = '\0';
        if (**ptr == '{')
        {
            parsing_entity = 1;
            continue;
        }
        if (**ptr == '}')
        {
            parsing_entity = 0;
            n--;
            continue;
        }
        if (parsing_entity)
        {
            enum entity_type type = atoi(*ptr);
            try = getline(ptr, &a, f);
            *(*ptr + try - 1) = '\0';
            double x = atof(*ptr);
            try = getline(ptr, &a, f);
            *(*ptr + try - 1) = '\0';
            double y = atof(*ptr);
            try = getline(ptr, &a, f);
            *(*ptr + try - 1) = '\0';
            double w = atof(*ptr);
            try = getline(ptr, &a, f);
            *(*ptr + try - 1) = '\0';
            double h = atof(*ptr);
            struct vector2 pos = { x, y };
            struct vector2 spd = { 0, 0 };
            struct transform transform = { h, w, pos, spd};
            struct entity *entity = create_entity(type, transform);
            *(entities + n) = *entity;
        }
    }
    free(ptr);
    map->entities = entities;
}

struct map *load_map(const char *filename)
{
    printf("entered load_map\n");
    struct map *new = malloc(sizeof(struct map));
    if (!new)
        return NULL;
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        printf("could not open file\n");
        free(new);
        return NULL;
    }
    else
    {
        printf("opened file\n");
        char **ptr = malloc(sizeof(char*));
        *ptr = NULL;
        size_t n = 64;
        enum block_type *blocks = NULL;
        size_t h = 10;
        size_t w = 10;
        size_t count = 0;
        while (1)
        { 
            size_t try = getline(ptr, &n, f);
            if (count == h + 4)
                break;
            *(*ptr + try - 1) = '\0';
            printf("parsed line : %s\n", *ptr);
            if (count == 0)
                new->width = atoi(*ptr);
            else if (count == 1)
                new->height = atoi(*ptr);
            else if (count == 2)
                new->start.x = atoi(*ptr);
            else if(count == 3)
                new->start.y = atoi(*ptr);
            else
            {
                if (!blocks)
                {
                    h = new->height;
                    w = new->width;
                    blocks = malloc(sizeof(enum block_type) * h * w);
                    if (!blocks)
                    {
                        free(new);
                        fclose(f);
                        return NULL;
                    }
                }
                for (size_t i = 0; i < w; i++)
                {
                    *(blocks + (count - 4) * w + i) = type_from_char(*(*ptr + i));
                }
            }
            count++;
        }
        if (atoi(*ptr) != 0)
        {
            printf("detected entities : %d\n", atoi(*ptr));
            parse_entities(f, new, atoi(*ptr));
        }
        new->blocks = blocks; 
        free(ptr);
        fclose(f);
    }
    return new;
}

void map_print(struct map *map)
{
    printf("width/height : %ld/%ld\n", map->width, map->height);
    for (size_t j = 0; j < map->height; j++)
    {
        for (size_t i = 0; i < map->width; i++)
        {
            printf("%c", char_from_type(*(map->blocks + map->width * j + i)));
        }
        printf("\n");
    }
}


enum block_type map_get_type(struct map *map, double i, double j)
{
    if (j < 0)
        return DEATH;
    else if (i >= map->width || j >= map->height || i < 0)
        return ICE;
    size_t i_int = i;
    size_t j_int = j;
    size_t pos = map->width * j_int + i_int;
    return map->blocks[pos];
}
