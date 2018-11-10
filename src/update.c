#include "update.h"
#include "entity.h"
#include "audio.h"
#include "player.h"

void update(struct gamestate *gamestate, int *inputs)
{
    if(inputs[PAUSE] == 1)
    {
        //Pause game
        Mix_PlayChannel(1, gamestate->sfxs[SFX_PAUSE], 0);
        if (gamestate->is_paused)
            Mix_ResumeMusic();
        else
            Mix_PauseMusic();
        gamestate->is_paused = !gamestate->is_paused;

    }
    else if (inputs[RESTART] == 1)
    {
        //Restart game
        kill_player(gamestate->player, gamestate);
    }
    else if (!gamestate->is_paused)
    {
        update_entity(gamestate->player, gamestate);
#if 0
        size_t nb_entities = gamestate->nb_entities;
        struct entity *entities = gamestate->entities;
        //Should not work if entities are deleted
        for (size_t i = 0; i < nb_entities; i++)
        {
             update_entity(entities[i], gamestate);
        }
#endif
    }
}
