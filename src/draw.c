#include "include/game.h"

#define BLOCK_SIZE 60
#define TEXTURE_MAX_AMOUNT 10


const char* ressource_files[] = 
{
    "resources/sprites/tiles.png",
    "bla.png"
};

void load_textures(struct gamestate *game)
{
    game->texture_count = 0;
    //struct SDL_Window *window = game->window;
    struct SDL_Renderer *renderer = game->renderer;

    //struct SDL_Texture *textures =
    //    malloc(sizeof(struct SDL_Texture) * TEXTURE_MAX_AMOUNT);
   // if (!textures)
   //     return;
    
    SDL_Surface *blocks = SDL_LoadBMP(ressource_files[0]);
    SDL_Texture *blocks_texture=SDL_CreateTextureFromSurface(renderer,blocks);
    game->texture_count++;
    game->textures = blocks_texture;
}

void init_window(struct gamestate *game)
{
    size_t height = game->map->height * BLOCK_SIZE;
    size_t width = game->map->width * BLOCK_SIZE;
    //size_t size = height * width;
    SDL_Window *window = SDL_CreateWindow("VGR GAME",\
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,\
            width, height, 0);
    if (!window)
        return;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, 0);
    if (!renderer)
    {
        warnx("renderer initialization failed\n");
    }
    game->window = window;
    game->renderer = renderer;
}

/*
struct SDL_Window *render_map(struct gamestate *game)
{
    
}
*/
