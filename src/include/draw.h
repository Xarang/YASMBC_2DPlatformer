#ifndef DRAW_H_
#define DRAW_H_

#include "gamestate.h"

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

void load_textures(struct gamestate *game);
void init_window(struct gamestate *game);
void render_game(struct gamestate *game);

#endif /* DRAW_H_*/
