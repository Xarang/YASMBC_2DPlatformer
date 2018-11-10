#ifndef AUDIO_H
# define AUDIO_H

#include "gamestate.h"

#define NB_SFX 2

enum sfxs
{
    SFX_JUMP,
    SFX_PAUSE
};

int init_audio(void);
void init_sfx(struct gamestate *game, Mix_Chunk **sfxs);
Mix_Music *play_music(const char *file);
void play_sfx(enum sfxs name, struct gamestate *game);
void free_sfx(Mix_Chunk **sfxs);
void close_audio(void);

#endif /* ! AUDIO_H */
