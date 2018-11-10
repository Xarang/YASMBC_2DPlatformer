#ifndef LIST_H
#define LIST_H

#include "include/game.h"

/*
struct list
{
    void *data;
    struct list *next;
}
*/

struct list *list_init(void *ptr)
{
    struct list *new = malloc(sizeof(struct list));
    if (!new)
        return NULL;
    new->data = ptr;
    new->next = ptr
}

void list_add(struct list *list, void *ptr)
{
    while (list->next != NULL)
    {
        list = list->next;
    }
    struct list *new = list_init(ptr);
    if (!new)
        return;
    list->next = new;
}

#endif /* LIST_H */
