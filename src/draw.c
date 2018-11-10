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
    
    SDL_Surface *blocks = IMG_Load(ressource_files[0]);
    if (!blocks)
        printf("could not load texture\n");
    SDL_Texture *blocks_texture=SDL_CreateTextureFromSurface(renderer,blocks);
    game->texture_count++;
    game->textures = blocks_texture;
}

void init_window(struct gamestate *game)
{
    size_t height = game->map->height * BLOCK_SIZE;
    size_t width = game->map->width * BLOCK_SIZE;
   // size_t size = height * width;
    SDL_Window *window = SDL_CreateWindow("VGR_GAME",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height, 0);
    if (!window)
        return;
    printf("window created\n");
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, 0);
    if (!renderer)
    {
        warnx("renderer initialization failed\n");
    }
    game->window = window;
    game->renderer = renderer;
}

void render_map(struct gamestate *game)
{
    struct SDL_Rect grass =
    {
        0,
        0,
        BLOCK_SIZE,
        BLOCK_SIZE
    };

    struct SDL_Rect select = 
    {
        0,
        0,
        BLOCK_SIZE,
        BLOCK_SIZE
    };

    struct map *map = game->map;
    size_t size = game->width * game->height;
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = 0; j < size. j++)
        {
                
        }
    }

    SDL_RenderCopy(game->renderer, game->textures, &grass, &select);
    SDL_RenderPresent(game->renderer);
}
