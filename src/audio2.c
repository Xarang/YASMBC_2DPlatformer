#include "audio.h"

void play_sfx(enum sfxs name, struct gamestate *game)
{
    Mix_PlayChannel(1, game->sfxs[name], 0);
}
