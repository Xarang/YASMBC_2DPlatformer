#include "update.h"
#include "entity.h"
#include "audio.h"
#include "player.h"
#include "input.h"

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
#if 0
        size_t nb_entities = gamestate->nb_entities;
        struct entity *entities = gamestate->entities;
        //Should not work if entities are deleted
        for (size_t i = 0; i < nb_entities; i++)
        {
             update_entity(entities[i], gamestate);
        }
#endif
        return get_game_status(player_status);
    }
    return RUNNING;
}
