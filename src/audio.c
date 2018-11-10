#include "audio.h"

int init_audio(void)
{
    int flags = MIX_INIT_OGG | MIX_INIT_MP3;
    if ((Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3) & flags) != flags)
    {
        fprintf(stderr, "Couldn't initialize audio\n");
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        fprintf(stderr, "Couldn't initialize mixer\n");
        return 1;
    }
    return 0;
}

Mix_Music *play_music(const char *file)
{
    Mix_Music *music = Mix_LoadMUS(file);
    if (!music)
        fprintf(stderr, "Error while loading music: %s\n", Mix_GetError());
    else
        Mix_PlayMusic(music, -1);
    return music;
}

void close_audio(void)
{
    Mix_CloseAudio();
    Mix_Quit();
}
