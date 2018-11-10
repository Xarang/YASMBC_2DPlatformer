#ifndef DRAW_H_
#define DRAW_H_

#include "game.h"

struct SDL_Surface *render_map(struct map *map);
void load_textures(struct gamestate *game);
void init_window(struct gamestate *game);

#endif /*DRAW_H_*/
