#include "update.h"
#include "entity.h"
#include "audio.h"
#include "player.h"
#include "input.h"
#include "list.h"

static enum game_status get_game_status(enum entity_status player_status)
{
    switch (player_status)
    {
    case ALIVE:
    case DIED:
        return RUNNING;
    case FINISH:
        return WIN;
    case ENTITY_ERROR:
        return GAME_ERROR;
    }
    return GAME_ERROR;
}

void update_entity_states(struct map *map)
{
    struct list *entities = map->entities;
    if (entities)
    {
        for (size_t i = 0; i < map->nb_entities; i++)
        {
            struct entity *current = entities->data;
            if (current->type == FOE_1 || current->type == BLOODY_FOE_1)
            {
                current->state++;
                current->state %= 3;
            }
            entities = entities->next;
        }
    }
}

enum game_status update(struct gamestate *gamestate, int *inputs)
{
    if(inputs[PAUSE] == 1)
    {
        //Pause game
        play_sfx(SFX_PAUSE, gamestate);
        if (gamestate->is_paused)
            Mix_ResumeMusic();
        else
            Mix_PauseMusic();
        gamestate->is_paused = !gamestate->is_paused;
        return RUNNING;
    }
    else if (inputs[RESTART] == 1)
    {
        //Restart game
        kill_player(gamestate->player, gamestate);
        return RUNNING;
    }
    else if (!gamestate->is_paused)
    {
        enum entity_status player_status = update_entity(gamestate->player,
                                                         gamestate);

        update_entity_states(gamestate->map);
#if 1
        size_t nb_entities = gamestate->map->nb_entities;
        struct list *entities = gamestate->map->entities;
        struct entity *entity;
        for (size_t i = 0; i < nb_entities; i++)
        {
            entity = list_get_n(entities, i);
            update_entity(entity, gamestate);
        }
#endif
        return get_game_status(player_status);
    }
    return RUNNING;
}
