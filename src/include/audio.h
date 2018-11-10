#ifndef AUDIO_H
# define AUDIO_H

#include "gamestate.h"

#define NB_SFX 1

enum sfxs
{
    SFX_JUMP
};

int init_audio(void);
void init_sfx(struct gamestate *game, Mix_Chunk **sfxs);
Mix_Music *play_music(const char *file);
void free_sfx(Mix_Chunk **sfxs);
void close_audio(void);

#endif /* ! AUDIO_H */
