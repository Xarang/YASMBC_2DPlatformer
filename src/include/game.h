#ifndef GAME_H_
#define GAME_H_

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <unistd.h>
#include <math.h>

//includes all the other headers..

#define BLOCK_SIZE 60

#include "vector2.h"
#include "gamestate.h"
#include "draw.h"
#include "map.h"
#include "entity.h"
#include "time_utils.h"

#endif /*GAME_H_*/
