#include "include/game.h"

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
    }
    return '.';
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
        char *blocks;
        size_t count = 0;
        while (1)
        { 
            size_t try = getline(ptr, &n, f);
            if (count > 3 && try > new->width + 1)
                break;
            *(*ptr + try - 1) = '\0';
            //printf("parsed line : %s\n", *ptr);
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
                size_t h = new->height;
                //printf("h detected : %zu\n", h);
                size_t w = new->width;
                //printf("w detected : %zu\n", w);
                blocks = malloc(sizeof(char) * h * w);
                if (!blocks)
                {
                    free(new);
                    fclose(f);
                    return NULL;
                }
                for (size_t i = 0; i < w; i++)
                {
                *(blocks + (count - 4) * w + i) = type_from_char(*(*ptr + i));
                }
            }
            count++;
        }
        new->blocks = blocks; 
        free(ptr);
        fclose(f);
    }
    printf("returning map\n");
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


enum block_type map_get_type(struct map *map, size_t i, size_t j)
{
    return *(map->blocks + map->width * j + i);
}

/*
int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    struct map *map = load_map(*(argv + 1));
    map_print(map);
    return 0;
}
*/
