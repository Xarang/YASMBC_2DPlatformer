#include "game.h"

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
   
    sleep(50000);
    
    game = game;
    SDL_Quit();
    return 0;
}
