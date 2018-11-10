#include "game.h"
#include "update.h"

struct gamestate *gamestate_init(void)
{
    struct gamestate *new = malloc(sizeof(struct gamestate));
    if (!new)
        return NULL;
    new->map = load_map("resources/maps/map_one");
    struct transform player_pos =
    {
        1.0 / 2.0,
        1.0 / 2.0,
        { new->map->start.x, new->map->start.y },
        { 0                , 0                 }
    };
    new->player = create_entity(PLAYER, player_pos);
    new->last_update_time = SDL_GetPerformanceCounter();
    new->is_paused = 0;
    init_window(new);
    warnx("window created");
    load_textures(new);
    warnx("textures loaded");

    return new;
}

int main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        return 1;
    //SDL_Init(SDL_INIT_EVERYTHING);

    struct gamestate *game = gamestate_init();
    /*
    render_game(game);
    sleep(500);
    */
    init_audio();
    Mix_Music *music = play_music("resources/audio/stage1.mp3");

    render_game(game);
    int inputs[NB_ACTION] =
    {
        0
    };

    Mix_Chunk *sfxs[NB_SFX] =
    {
        0
    };
    init_sfx(game, sfxs);

    while (1)
    {
        get_input(inputs, game);
        if (game->inputs[EXIT])
            break;
         for (size_t i = 0; i < NB_ACTION; i++)
         {
             if (game->inputs[i])
                 printf("Button pressed: %ld, Value: %d\n", i, game->inputs[i]);
             if (game->inputs[JUMP] == 1)
                 Mix_PlayChannel(1, game->sfxs[SFX_JUMP], 0);
         }
        update(game, inputs);

        SDL_RenderClear(game->renderer);
        render_game(game);
        SDL_Delay(16.66);
    }
    free_sfx(game->sfxs);
    Mix_FreeMusic(music);
    close_audio();
    SDL_Quit();
    return 0;
}
