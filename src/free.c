#include "game.h"

void exit_game(struct gamestate *game)
{
    free_sfx(game->sfxs);
    Mix_FreeMusic(game->music);
    close_audio();
    free_textures(game->textures);
    SDL_DestroyWindow(game->window);
    if (game->map)
    {
        destroy_map(game->map);
    }
    destroy_entity(game->player);
    free(game);
    SDL_Quit();
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
