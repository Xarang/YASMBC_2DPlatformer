#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "game.h"

struct gamestate
{
    struct map *map;
    struct entity *player;
    uint64_t last_update_time;
    enum action inputs[NB_ACTION];
    //SDL SurfaceS
    struct SDL_Window *window;
    struct SDL_Renderer *renderer;
    struct SDL_Texture *textures;
    size_t texture_count;
};

struct gamestate *init(void);


#endif /*GAMESTATE_H_*/
