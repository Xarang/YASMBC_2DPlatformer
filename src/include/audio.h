#ifndef AUDIO_H
# define AUDIO_H

#include <SDL_mixer.h>

int init_audio(void);
Mix_Music *play_music(const char *file);
void close_audio(void);

#endif /* ! AUDIO_H */
