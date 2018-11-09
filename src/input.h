#ifndef INPUT_H
# define INPUT_H

#define NB_ACTION 6

enum action
{
    LEFT,
    RIGHT,
    JUMP,
    RUN,
    PAUSE,
    RESTART
};

void get_input(enum action inputs[NB_ACTION]);

#endif /* ! INPUT_H */
