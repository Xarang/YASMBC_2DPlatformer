#ifndef GAME_H_
#define GAME_H_

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <SDL.h>
#include <SDL_image.h>
#include <err.h>
#include <unistd.h>
#include <math.h>

#define BLOCK_SIZE 40

//includes all the other headers..

#include "vector2.h"
#include "input.h"
#include "gamestate.h"
#include "draw.h"
#include "map.h"
#include "entity.h"
#include "time_utils.h"
#include "audio.h"
#include "foe_1.h"
#include "foe_2.h"
#include "free.h"
#include "list.h"


#endif /*GAME_H_*/
