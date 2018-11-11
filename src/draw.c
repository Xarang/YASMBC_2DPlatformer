#include "game.h"

//should merge the two values below

#define NB_TEXTURES 5
#define NB_SPRITES 10


enum texture_id
{
    BACKGROUND = 0,
    MAP        = 1,
    PLAYER_TXR = 2,
    FOES       = 3,
    UI         = 4
};

struct texture
{
    enum texture_id id;
    char *name;
    SDL_Rect rect;
};

#define PLAYER_SPRITE_LEN 165

#define BLOCK_SIZE_F 60
#define FOES_SIZE_F 220 

struct texture textures[NB_SPRITES] =
{
    { .id = MAP, .name = "grass", .rect = {
                                              0,
                                              0,
                                              BLOCK_SIZE_F,
                                              BLOCK_SIZE_F
                                          }},
    { .id = MAP, .name = "player",.rect = { 
                                              BLOCK_SIZE_F * 7,
                                              BLOCK_SIZE_F * 5,
                                              BLOCK_SIZE_F / 2,
                                              BLOCK_SIZE_F / 2 
                                          }},
    { .id = MAP, .name = "finish", .rect = {
                                               BLOCK_SIZE_F * 3, 
                                               BLOCK_SIZE_F * 4,
                                               BLOCK_SIZE_F,
                                               BLOCK_SIZE_F 
                                           }},
    { .id = MAP, .name = "ice", .rect = { 
                                            BLOCK_SIZE_F * 5.2, 
                                            BLOCK_SIZE_F * 2.2,
                                            BLOCK_SIZE_F * 0.7, 
                                            BLOCK_SIZE_F * 0.7 
                                        }},
    { .id = BACKGROUND, .name = "forestbg1", .rect = {
                                                         0, 
                                                         0, 
                                                         640, 
                                                         480 
                                                     }},

    { .id = PLAYER_TXR, .name = "idle", .rect = {
                                                    1, 
                                                    1, 
                                                    PLAYER_SPRITE_LEN - 1,
                                                    PLAYER_SPRITE_LEN - 1
                                                }},
    { .id = PLAYER_TXR, .name = "jump", .rect = {
                                                    PLAYER_SPRITE_LEN * 5 + 1,
                                                    PLAYER_SPRITE_LEN * 1 + 1,
                                                    PLAYER_SPRITE_LEN - 1,
                                                    PLAYER_SPRITE_LEN - 1
                                                }},
    { .id  = PLAYER_TXR, .name = "full", .rect = {
                                                     1, 
                                                     PLAYER_SPRITE_LEN * 2,
                                                     PLAYER_SPRITE_LEN - 1,
                                                     PLAYER_SPRITE_LEN - 1
                                                 }},
    { .id = FOES, .name = "buzzaxe", .rect = {
                                                 0, 
                                                 0, 
                                                 FOES_SIZE_F, 
                                                 FOES_SIZE_F
                                             }},
    { .id = UI, .name = "veil", .rect = { 
                                            0, 
                                            0, 
                                            1, 
                                            1 
                                        }}
};

struct SDL_Rect get_sprite(const char *name)
{
    for (size_t i = 0; i < NB_SPRITES; i++)
    {
        if (strcmp(name, textures[i].name) == 0)
        {
            return textures[i].rect;
        }
    }
    SDL_Rect null = {0, 0, 0, 0};
    return null;
}

const char* ressource_files[NB_TEXTURES] = 
{
    "resources/sprites/forestbg.png",
    "resources/sprites/tiles.png",
    "resources/sprites/cube.png",
    "resources/sprites/foes.png",
    "resources/sprites/tiles.png"
};

void load_textures(struct gamestate *game)
{
    warnx("entered load_textures");
    game->texture_count = 0;
    struct SDL_Renderer *renderer = game->renderer;
    //struct SDL_Window *window = game->window;
    struct list *textures;
    for (size_t i = 0; i < NB_TEXTURES - 1; i++)
    {
        SDL_Surface *blocks = IMG_Load(ressource_files[i]);
        if (!blocks)
            printf("could not load texture\n");
        SDL_Texture *blocks_texture=SDL_CreateTextureFromSurface(renderer,blocks); 
        if (!blocks_texture)
            printf("could not turn image into texture\n");
        if (i == 0)
            textures = list_init(blocks_texture);
        else
            list_add(textures, blocks_texture);
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
   // size_t size = height * width;
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
    SDL_Texture *texture = list_get_n(game->textures, BACKGROUND);
    if (!texture)
        warnx("render_background : texture not found");
    struct SDL_Rect select =
    {
        0,
        0,
        game->map->width  * BLOCK_SIZE,
        game->map->height * BLOCK_SIZE
    };
    struct SDL_Rect sprite = get_sprite("forestbg1");
    SDL_RenderCopy(renderer, texture, &sprite, &select);
}

void render_map(struct gamestate *game)
{
    SDL_Renderer *renderer = game->renderer;
    SDL_Texture *texture = list_get_n(game->textures, MAP);
    struct map *map = game->map;

   // struct SDL_Rect *rect[map->width][map->height];
    // size_t size = game->map->width * game->map->height;
    map_print(map);
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
            {
                sprite = get_sprite("grass");
            }
            else if (current == FINISH)
            {
                sprite = get_sprite("finish");
            }
            else if (current == ICE)
            {
                sprite = get_sprite("ice");
            }
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
    warnx("player position : %f/%f\n",player_tf.pos.x, player_tf.pos.y);
    warnx("on image : %d / %d / %d / %d\n", player_position.x, player_position.y,player_position.w,player_position.h);

    struct SDL_Rect sprite = get_sprite("full");
    SDL_RenderCopy(renderer, texture, &sprite, &player_position); 
}


void render_UI(struct gamestate *game)
{
    SDL_Renderer *renderer = game->renderer;
    SDL_Texture *texture = list_get_n(game->textures, UI);
    struct map *map = game->map;
   
    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);

    struct SDL_Rect sprite = get_sprite("veil");
    printf("veil rect : %d/%d/%d/%d\n", sprite.x, sprite.y, sprite.w, sprite.h);
    struct SDL_Rect screen =
    {
        0,
        0,
        map->width,
        map->height
    };

   // if (game->is_paused)
   // {
        SDL_RenderCopy(renderer, texture, &sprite, &screen); 
  //  }
}

void render_entities(struct gamestate *game)
{
    warnx("entered entities rendering");
    SDL_Renderer *renderer = game->renderer;
    SDL_Texture *texture = list_get_n(game->textures, FOES); 
    struct map *map = game->map;
    for (size_t i = 0; i < map->nb_entities; i++)
    {
        struct entity *current = map->entities + i;
        char *name = "foe";
        switch (current->type)
        {
            case PLAYER:
                //?
                break;
            case FOE_1:
                name = "buzzaxe";
                break;
            case FOE_2:
                name = "gagaga";
                break;
        }
        struct SDL_Rect sprite = get_sprite(name);
        struct transform transform = current->transform;
        struct SDL_Rect pos = { transform.pos.x, transform.pos.y,
                                transform.width, transform.height };
        SDL_RenderCopy(renderer, texture, &sprite, &pos);
    }
    warnx("exit render entities..");
}

void render_game(struct gamestate *game)
{
    render_background(game);
    render_map(game);
    render_player(game);
    warnx("will try to render entities..");
    //render_entities(game);
    render_UI(game);
    SDL_RenderPresent(game->renderer);
}

