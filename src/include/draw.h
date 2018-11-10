#ifndef DRAW_H_
#define DRAW_H_

#include "gamestate.h"

void load_textures(struct gamestate *game);
void init_window(struct gamestate *game);
void render_game(struct gamestate *game);

#endif /* DRAW_H_*/
