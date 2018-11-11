#include "game.h"
#include "update.h"

#define NB_MAPS 3

struct gamestate *gamestate_init(void)
{
    struct gamestate *new = malloc(sizeof(struct gamestate));
    if (!new)
        return NULL;
    new->map = load_map("resources/maps/map_one");
    map_print(new->map);
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

static int switch_map(struct gamestate *game, int ind, Mix_Music *music)
{
    static char *maps[NB_MAPS] =
    {
        "resources/maps/map_one",
        "resources/maps/map_two",
        "resources/maps/map_three"
    };
    static char *musics[NB_MAPS] =
    {
        "resources/audio/stage1.mp3",
        "resources/audio/stage2.mp3",
        "resources/audio/stage2.mp3"
    };
    if (ind + 1 <= NB_MAPS)
        return -1;
    ind++;
    Mix_FreeMusic(music);
    Mix_Music *fanfare = play_music("resources/audio/win.mp3", 1);
    //destroy_map(game->map);
    game->map = load_map(maps[ind]);
    reset_entity(game->player);

    SDL_Event keyevent;
    while (SDL_WaitEvent(&keyevent))
    {
        if (keyevent.type == SDL_KEYDOWN || keyevent.type == SDL_KEYUP)
            break;
    }

    Mix_FreeMusic(fanfare);
    music = play_music(musics[ind], -1);
    return ind;
}

int main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        return 1;

    struct gamestate *game = gamestate_init();

    init_audio();
    Mix_Music *music = play_music("resources/audio/stage1.mp3", -1);
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

    int map = 0;
    while (1)
    {
        get_input(inputs, game);
        if (game->inputs[EXIT])
            break;
        for (size_t i = 0; i < NB_ACTION; i++)
        {
            if (game->inputs[i])
                printf("Button pressed: %ld, Value: %d\n", i, game->inputs[i]);
        }
        int win = 0;
        /*int win = */update(game, inputs);

        SDL_RenderClear(game->renderer);
        render_game(game);

        if (win)
        {
            map = switch_map(game, map, music);
            if (map < 0)
                break;
        }

        SDL_Delay(16);
    }
    free_sfx(game->sfxs);
    Mix_FreeMusic(music);
    close_audio();
    SDL_Quit();
    return 0;
}
