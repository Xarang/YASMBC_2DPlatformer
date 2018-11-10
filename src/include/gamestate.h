#ifndef GAMESTATE_H_
#define GAMESTATE_H_

struct gamestate
{
    struct map *map;
    //player
    //deltatime
    //inputs[]
    //SDL SurfaceS
    struct SDL_Window *window;
    struct SDL_Renderer *renderer;
    struct SDL_Texture *textures;
    size_t texture_count;
};

struct gamestate *init(void);


#endif /*GAMESTATE_H_*/
