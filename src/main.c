#include "game.h"
#include "update.h"

#define NB_MAPS 6

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
    warnx("player created");
    new->last_update_time = SDL_GetPerformanceCounter();
    new->is_paused = 0;
    init_window(new);
    warnx("window created");
    load_textures(new);
    warnx("textures loaded");

    return new;
}

Mix_Music *switch_map(struct gamestate *game, int *ind, Mix_Music *music)
{
    static char *maps[NB_MAPS] =
    {
        "resources/maps/map_one",
        "resources/maps/map_two",
        "resources/maps/map_three",
        "resources/maps/map_four",
        "resources/maps/map_five",
        "resources/maps/map_six"
    };
    static char *musics[NB_MAPS] =
    {
        "resources/audio/stage1.mp3",
        "resources/audio/stage1.mp3",
        "resources/audio/stage1.mp3",
        "resources/audio/stage2.mp3",
        "resources/audio/stage2.mp3",
        "resources/audio/stage2.mp3"
    };
    *ind += 1;
    if (*ind >= NB_MAPS)
        return music;
    Mix_FreeMusic(music);
    Mix_Music *fanfare = play_music("resources/audio/win.mp3", 1);
    destroy_map(game->map);
    game->map = load_map(maps[*ind]);
    game->player->init_transform.pos.x = game->map->start.x;
    game->player->init_transform.pos.y = game->map->start.y;
    reset_entity(game->player);

    while (1)
    {
        SDL_PumpEvents();
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_RETURN])
            break;
    }
    SDL_SetWindowSize(game->window, game->map->width * BLOCK_SIZE,
            game->map->height * BLOCK_SIZE);

    Mix_FreeMusic(fanfare);
    Mix_Music *tmp = play_music(musics[*ind], -1);
    return tmp;
}

int main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        return 1;

    struct gamestate *game = gamestate_init();

    init_audio();
    game->music = play_music("resources/audio/stage1.mp3", -1);
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
    while (map < NB_MAPS)
    {
        get_input(inputs, game);
        if (game->inputs[EXIT])
            break;
        enum game_status status = update(game, inputs);
        SDL_RenderClear(game->renderer);
        render_game(game);
        SDL_Delay(16.66);

        if (status == WIN)
        {
            game->music = switch_map(game, &map, game->music);
        }
    }
    exit_game(game);
    return 0;
}
