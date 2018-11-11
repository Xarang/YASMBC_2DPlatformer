#include "game.h"

static enum block_type type_from_char(char c)
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
        case 'R':
            return ROCK;
        case 'S':
            return STONE;
        case 'L':
            return GRASS_ROCK;
        default :
            return VOID;
    }
}

static char char_from_type(enum block_type type)
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
        case ROCK:
            return 'R';
        case GRASS_ROCK:
            return 'L';
        case STONE:
            return 'S';
    }
    return '.';
}


static void parse_entity(FILE *f, struct list **entities)
{
    char *ptr = NULL;
    size_t a = 0;
    int type = 0;
    double x = 0;
    double y = 0;
    double h = 0;
    double w = 0;
    double s_x = 0;
    double s_y = 0;
    for (size_t i = 0; i < 8; i++)
    {
        if (ptr)
        {
            free(ptr);
        }
        ptr = NULL;
        a = 0;
        getline(&ptr, &a, f);
        double val = 0;
        if (i < 7)
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
        else if (i == 5)
            s_x = val;
        else if (i == 6)
            s_y = val;
        else
        {
            struct vector2 pos = { x, y };
            struct vector2 spd = { s_x, s_y };
            struct transform transform = { h, w, pos, spd};
            struct entity *entity = create_entity(type, transform);
            if (!(*entities))
            {
                *entities = list_init(entity);
            }
            else
            {
                list_add(*entities, entity);
            }
            free(ptr);
            ptr = NULL;
        }
    }
}

static void parse_entities(FILE *f, struct map *map, int n)
{
    char *ptr = NULL;
    struct list *entities = NULL;
    map->nb_entities = n;
    int parsing_entity = 0;
    size_t a = 0;
    while (n > 0)
    {
        int try = getline(&ptr, &a, f);
        *(ptr + try - 1) = '\0';
        if (*ptr == '{')
        {
            free(ptr);
            parsing_entity = 1;
            ptr = NULL;
            a = 0;
        }
        if (parsing_entity)
        {
            parse_entity(f, &entities);
        }
        a = 0;
        parsing_entity = 0;
        n--;
    }
    map->entities = entities;
    warnx("exiting entity parsing");
}

enum block_type *parse_map(FILE *f, struct map *new, char **ptr)
{
    *ptr = NULL;
    size_t n = 0;
    enum block_type *blocks = NULL;
    size_t h = 10;
    size_t w = 10;
    size_t count = 0;
    while (1)
    {
        size_t try = getline(ptr, &n, f);
        *(*ptr + try - 1) = '\0';
        if (count == h + 5)
            break;
        if (count == 0)
            new->world_id = atoi(*ptr);
        else if (count == 1)
            new->width = atoi(*ptr);
        else if (count == 2)
            new->height = atoi(*ptr);
        else if (count == 3)
            new->start.x = atoi(*ptr);
        else if(count == 4)
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
                *(blocks + (count - 5)*w + i)=type_from_char(*(*ptr + i));
        }
        if (*ptr)
        {
            free(*ptr);
            *ptr = NULL;
            n = 0;
        }
        count++;
    }
    return blocks;
}

struct map *load_map(const char *filename)
{
    struct map *new = malloc(sizeof(struct map));
    if (!new)
        return NULL;
    new->nb_entities = 0;
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        free(new);
        return NULL;
    }
    else
    {
        char **ptr = malloc(sizeof(char*));
        enum block_type *blocks = parse_map(f, new, ptr);
        if (atoi(*ptr) != 0)
        {
            parse_entities(f, new, atoi(*ptr));
            free(*ptr);
            *ptr = NULL;
        }
        new->blocks = blocks;
        if (ptr)
        {
            free(ptr);
        }
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
    if (j >= map->height)
        return DEATH;
    else if (i >= map->width || j < 0 || i < 0)
        return ICE;
    size_t i_int = i;
    size_t j_int = j;
    size_t pos = map->width * j_int + i_int;
    return map->blocks[pos];
}
