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
        { 0               , 0                }
    };
    new->player = create_entity(PLAYER, player_pos);
    new->last_update_time = SDL_GetPerformanceFrequency();
    init_window(new);
    load_textures(new);

    return new;
}

int main(void)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        return 1;
    //SDL_Init(SDL_INIT_EVERYTHING);

    struct gamestate *game = gamestate_init();
    render_map(game);
    int inputs[NB_ACTION] =
    {
        0
    };
    while (1)
    {
        get_input(inputs, game);
        /* for (size_t i = 0; i < NB_ACTION; i++) */
        /* { */
        /*     if (inputs[i]) */
        /*         printf("Button pressed: %ld\n", i); */
        /* } */
        //render_map(game);
    }
    SDL_Quit();
    return 0;
}
