#include "game.h"

void exit_game(struct gamestate *game)
{
    free_sfx(game->sfxs);
    printf("sfxs freed\n");
    Mix_FreeMusic(game->music);
    printf("Music freed\n");
    close_audio();
    printf("audio closed\n");
    free_textures(game->textures);
    printf("textures freed\n");
    SDL_DestroyWindow(game->window);
    printf("window destroyed\n");
    if (game->map)
    {
        destroy_map(game->map);
        printf("map destroyed\n");
    }
    destroy_entity(game->player);
    printf("player destroyed\n");
    free(game);
    printf("gamestate structure freed\n");
    SDL_Quit();
    printf("SDL stopped\n");
}


void free_textures(struct list *textures)
{
    struct list *list = textures;
    while (list)
    {
        struct SDL_Texture *current = list->data;
        SDL_DestroyTexture(current);
        struct list *node = list;
        list = list->next;
        free(node);
    }
}

void free_entities(struct list *entities)
{
    struct list *list = entities;
    while (list)
    {
        struct entity *current = list->data;
        destroy_entity(current);
        struct list *node = list;
        list = list->next;
        free(node);
    }
}

void destroy_map(struct map *map)
{
    free_entities(map->entities);
    free(map->blocks);
    free(map);
}
