#include "game.h"
#include "draw.h"

struct sprite sprites[NB_SPRITES] =
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
    
    { .id = MAP, .name = "rock", .rect = {
                                            BLOCK_SIZE_F * 1,
                                            BLOCK_SIZE_F * 1,
                                            BLOCK_SIZE_F * 1,
                                            BLOCK_SIZE_F * 1
                                        }},
    { .id = MAP, .name = "grass_rock", .rect = {
                                            BLOCK_SIZE_F * 0,
                                            BLOCK_SIZE_F * 1,
                                            BLOCK_SIZE_F * 1,
                                            BLOCK_SIZE_F * 1
                                        }},
    { .id = MAP, .name = "stone", .rect = {
                                            BLOCK_SIZE_F * 0,
                                            BLOCK_SIZE_F * 4,
                                            BLOCK_SIZE_F * 1,
                                            BLOCK_SIZE_F * 1
                                        }},
    { .id = BACKGROUND_0, .name = "forestbg1", .rect = {
                                                           0,
                                                           0,
                                                           640,
                                                           480
                                                       }},

    { .id = BACKGROUND_1, .name = "mountainbg1", .rect = {
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
    { .id = FOES, .name = "b_buzzaxe01", .rect = {
                                                 0,
                                                 FOES_SIZE_F,
                                                 FOES_SIZE_F,
                                                 FOES_SIZE_F
                                             }},

    { .id = FOES, .name = "b_buzzaxe02", .rect = {
                                                 FOES_SIZE_F,
                                                 FOES_SIZE_F,
                                                 FOES_SIZE_F,
                                                 FOES_SIZE_F
                                             }},
    { .id = FOES, .name = "b_buzzaxe03", .rect = {
                                            FOES_SIZE_F * 2,
                                            FOES_SIZE_F,
                                            FOES_SIZE_F,
                                            FOES_SIZE_F
                                        }},

    { .id = FOES, .name = "buzzaxe01", .rect = {
                                                 0,
                                                 0,
                                                 FOES_SIZE_F,
                                                 FOES_SIZE_F
                                             }},

    { .id = FOES, .name = "buzzaxe02", .rect = {
                                                 FOES_SIZE_F,
                                                 0,
                                                 FOES_SIZE_F,
                                                 FOES_SIZE_F
                                             }},
    { .id = FOES, .name = "buzzaxe03", .rect = {
                                            FOES_SIZE_F * 2,
                                            0,
                                            FOES_SIZE_F,
                                            FOES_SIZE_F
                                        }}
};

struct SDL_Rect get_sprite(const char *name)
{
    for (size_t i = 0; i < NB_SPRITES; i++)
    {
        if (strcmp(name, sprites[i].name) == 0)
        {
            return sprites[i].rect;
        }
    }
    SDL_Rect null = {0, 0, 0, 0};
    return null;
}

struct SDL_Rect get_entity_sprite(struct entity *entity)
{
    enum entity_type type = entity->type;
    int state = entity->state;
    switch (type)
    {
        case PLAYER:
            return get_sprite("player");
        case FOE_1:
            if (state == 0)
                return get_sprite("buzzaxe01");
            else if (state == 1)
                return get_sprite("buzzaxe02");
            else
                return get_sprite("buzzaxe03");
            break;
        case BLOODY_FOE_1:
            if (state == 0)
                return get_sprite("b_buzzaxe01");
            else if (state == 1)
                return get_sprite("b_buzzaxe02");
            else
                return get_sprite("b_buzzaxe03");
            break;
        case FOE_2:

            break;
    }
    SDL_Rect null = { 0, 0, 0, 0 };
    return null;
}
