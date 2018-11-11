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
   // char **ptr = malloc(sizeof(char*));
   // if (!ptr)
   //     return;
    char *ptr = NULL;
    map->nb_entities = n;
    int parsing_entity = 0;
    size_t a = 0;
    struct entity *entities = malloc(sizeof(struct entity) * n);
    if (!entities)
    {
        free(ptr);
        return;
    }
    while (n > 0)
    {
        warnx("entered while");
        warnx("about to call getline. a: %zu. *ptr is null : %d", a, ptr == NULL);
        int try = getline(&ptr, &a, f);
        //if (!(*ptr))
        //    warnx("ptr null");    
        warnx("parsed line : %s", ptr);
        *(ptr + try - 1) = '\0';
        if (*ptr == '{')
        {
            parsing_entity = 1;
            ptr = NULL;
            a = 0;
            continue;
        }
        if (parsing_entity)
        {
            int type = 0;
            double x = 0;
            double y = 0;
            double h = 0;
            double w = 0;
            for (size_t i = 0; i < 6; i++)
            {
                if (ptr)
                {
                    warnx("attempting to free ptr");
                    free(ptr);
                    warnx("ptr freed");
                }
                ptr = NULL;
                a = 0; 
                try = getline(&ptr, &a, f); 
                double val = 0;
                if (i < 5)
                {
                    val = atof(ptr);
                }
                if (i == 0)
                    type = val; 
                else if (i == 1)
                    x = val;
                else if (i == 2)
                    y = val;
                else if (i == 3)
                    w = val;
                else if (i == 4)
                    h = val;
                else
                {
                    struct vector2 pos = { x, y };
                    struct vector2 spd = { 0, 0 };
                    struct transform transform = { h, w, pos, spd};
                    struct entity *entity = create_entity(type, transform);
                    *(entities + n) = *entity;
                    free(ptr);
                    ptr = NULL;
                    a = 0;
                    parsing_entity = 0;
                    n--;
                    warnx("entity created");
                }
            }
        }
    }
    warnx("exited while");
   // if (ptr)
   //     free(ptr);
    map->entities = entities;
    warnx("exiting entity parsing");
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
        size_t n = 0;
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
            if (*ptr)
            {
                free(*ptr);
                *ptr = NULL;
                n = 0;
            }
            count++;
        }
        if (atoi(*ptr) != 0)
        {
            printf("detected entities : %d\n", atoi(*ptr));
       //     parse_entities(f, new, atoi(*ptr));
        }
        new->blocks = blocks; 
        if (ptr)
        {
            free(ptr);
        }
        fclose(f);
    }
    warnx("exiting parsing");
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
    if (j >= map->height)
        return DEATH;
    else if (i >= map->width || j < 0 || i < 0)
        return ICE;
    size_t i_int = i;
    size_t j_int = j;
    size_t pos = map->width * j_int + i_int;
    return map->blocks[pos];
}
