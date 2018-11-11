#include "game.h"

//should merge the two values below


const char* ressource_files[NB_TEXTURES] =
{
    "resources/sprites/forestbg.png",
    "resources/sprites/forestbg2.png",
    "resources/sprites/tiles.png",
    "resources/sprites/cube.png",
    "resources/sprites/foes.png",
    "resources/sprites/tiles.png"
};

void load_textures(struct gamestate *game)
{
    game->texture_count = 0;
    struct SDL_Renderer *renderer = game->renderer;
    //struct SDL_Window *window = game->window;
    struct list *textures;
    for (size_t i = 0; i < NB_TEXTURES - 1; i++)
    {
        SDL_Surface *blocks = IMG_Load(ressource_files[i]);
        if (!blocks)
            warnx("could not open image");
        SDL_Texture *blocks_txr=SDL_CreateTextureFromSurface(renderer,blocks);
        if (!blocks_txr)
            warnx("could not load texture");
        if (i == 0)
            textures = list_init(blocks_txr);
        else
            list_add(textures, blocks_txr);
    }


    SDL_Texture *veil_texture =SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,
                                            SDL_TEXTUREACCESS_TARGET, 1, 1);

    SDL_SetTextureBlendMode(veil_texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, veil_texture);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
    SDL_SetRenderDrawColor(renderer, 127, 127, 127, 127);
    SDL_RenderFillRect(renderer, NULL);

    list_add(textures, veil_texture);
    game->textures = textures;
}

void init_window(struct gamestate *game)
{
    size_t height = game->map->height * BLOCK_SIZE;
    size_t width = game->map->width * BLOCK_SIZE;
    SDL_Window *window = SDL_CreateWindow("VGR_GAME",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            width, height, 0);
    if (!window)
        return;
    printf("window created\n");

    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, 0);
    game->window = window;
    game->renderer = renderer;
}

void render_background(struct gamestate *game)
{
    SDL_Renderer *renderer = game->renderer;
    SDL_Texture *texture;
    struct SDL_Rect sprite; 
    if (game->map->world_id == 0)
    {
        sprite = get_sprite("forestbg1");
        texture = list_get_n(game->textures, BACKGROUND_0);
    }
    else
    {
        sprite = get_sprite("mountainbg1");
        texture = list_get_n(game->textures, BACKGROUND_1);
    }
    if (!texture)
        warnx("render_background : texture not found");
    struct SDL_Rect select =
    {
        0,
        0,
        game->map->width  * BLOCK_SIZE,
        game->map->height * BLOCK_SIZE
    };
    SDL_RenderCopy(renderer, texture, &sprite, &select);
}

void render_map(struct gamestate *game)
{
    SDL_Renderer *renderer = game->renderer;
    SDL_Texture *texture = list_get_n(game->textures, MAP);
    struct map *map = game->map;
    for (size_t i = 0; i < map->width; i++)
    {
        for (size_t j = 0; j < map->height; j++)
        {
            enum block_type current = map_get_type(map, i, j);
            struct SDL_Rect select =
            {
                BLOCK_SIZE * i,
                BLOCK_SIZE * j,
                BLOCK_SIZE,
                BLOCK_SIZE
            };
            struct SDL_Rect sprite;
            if (current == BLOCK)
                sprite = get_sprite("grass");
            else if (current == FINISH)
                sprite = get_sprite("finish");
            else if (current == ICE)
                sprite = get_sprite("ice");
            else if (current == ROCK)
                sprite = get_sprite("rock");
            else if (current == GRASS_ROCK)
                sprite = get_sprite("grass_rock");
            else if (current == STONE)
                sprite = get_sprite("stone");
            else
            {
                continue;
            }
            SDL_RenderCopy(renderer, texture, &sprite, &select);
        }
    }
}

void render_player(struct gamestate *game)
{
    SDL_Renderer *renderer = game->renderer;
    SDL_Texture *texture = list_get_n(game->textures, PLAYER_TXR);
    struct transform player_tf = game->player->transform;

    struct SDL_Rect player_position =
    {
        BLOCK_SIZE * (player_tf.pos.x - player_tf.width / 2),
        BLOCK_SIZE * (player_tf.pos.y - player_tf.height),
        BLOCK_SIZE * player_tf.width,
        BLOCK_SIZE * player_tf.height
    };
    struct SDL_Rect sprite = get_sprite("full");
    SDL_RenderCopy(renderer, texture, &sprite, &player_position);
}

void rendering_setup(struct gamestate *game)
{
    SDL_Renderer *renderer = game->renderer;

    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
}

void render_entities(struct gamestate *game)
{
    SDL_Renderer *renderer = game->renderer;
    SDL_Texture *texture = list_get_n(game->textures, FOES);
    struct map *map = game->map;
    struct list *entities = map->entities;
    for (size_t i = 0; i < map->nb_entities; i++)
    {
        struct entity *current = entities->data;
        print_entity(current);
        struct SDL_Rect sprite = get_entity_sprite(current);
        struct transform transform = current->transform;
        struct SDL_Rect pos =
        {
            (transform.pos.x - transform.width / 2) * BLOCK_SIZE,
            (transform.pos.y - transform.height / 2) * BLOCK_SIZE,
            transform.width * BLOCK_SIZE,
            transform.height* BLOCK_SIZE
        };
        SDL_RenderCopy(renderer, texture, &sprite, &pos);
        entities = entities->next;
    }
}

void render_game(struct gamestate *game)
{
    rendering_setup(game);
    render_background(game);
    render_map(game);
    render_player(game);
    render_entities(game);
    SDL_RenderPresent(game->renderer);
}

