#include "update.h"

void update(struct gamestate *gamestate, int inputs[NB_ACTION])
{
    if(inputs[PAUSE])
    {
        //Pause game
    }
    else if (inputs[RESTART])
    {
        //Restart game
    }
    else
    {
        size_t nb_entities = gamestate->nb_entities;
        struct entity entities = gamestate->entities;
        //Should not work if entities are deleted
        for (size_t i = 0; i < nb_entities; i++)
        {
            update_entity(entities[i], gamestate);
        }
    }
}
