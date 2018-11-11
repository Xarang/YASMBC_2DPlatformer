#ifndef SPRITE_H
#define SPRITE_H

#include "game.h"

#define NB_SPRITES 15
#define PLAYER_SPRITE_LEN 165
#define BLOCK_SIZE_F 60
#define FOES_SIZE_F 220

struct sprite
{
    enum texture_id id;
    char *name;
    SDL_Rect rect;
};

struct SDL_Rect get_sprite(const char *name);
struct SDL_Rect get_entity_sprite(struct entity *entity);

#endif
