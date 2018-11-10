#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include <stddef.h>
#include <stdint.h>
#include <SDL_mixer.h>

struct gamestate
{
    struct map *map;
    struct entity *player;
    uint64_t last_update_time;
    int *inputs;
    //SDL SurfaceS
    struct SDL_Window *window;
    struct SDL_Renderer *renderer;
    struct list *textures;
    Mix_Chunk **sfxs;
    size_t texture_count;
};

struct gamestate *init(void);


#endif /*GAMESTATE_H_*/
