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

void init_sfx(struct gamestate *game, Mix_Chunk **sfxs)
{
    const char* sfx_list[NB_SFX] =
    {
        "resources/audio/jump.wav"
    };
    for (size_t i = 0; i < NB_SFX; i++)
    {
        Mix_Chunk *sfx = Mix_LoadWAV(sfx_list[i]);
        if (!sfx)
            fprintf(stderr, "Error while loading SFX: %s\n", Mix_GetError());
        else
            sfxs[i] = sfx;
    }
    game->sfxs = sfxs;
}

void free_sfx(Mix_Chunk **sfxs)
{
    for (size_t i = 0; i < NB_SFX; i++)
        Mix_FreeChunk(sfxs[i]);
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
