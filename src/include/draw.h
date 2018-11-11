#ifndef DRAW_H_
#define DRAW_H_

#include "gamestate.h"

#define NB_TEXTURES 6

enum texture_id
{
    BACKGROUND_0 = 0,
    BACKGROUND_1 = 1,
    MAP          = 2,
    PLAYER_TXR   = 3,
    FOES         = 4,
    UI           = 5
};

struct texture
{
    enum texture_id id;
    char *name;
    SDL_Rect rect;
};

void load_textures(struct gamestate *game);
void init_window(struct gamestate *game);
void render_game(struct gamestate *game);

#endif /* DRAW_H_*/
