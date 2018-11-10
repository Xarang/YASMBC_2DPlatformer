#ifndef LIST_H
#define LIST_H

//structure used to contains our renderers

#include <stdlib.h>
#include <stddef.h>

struct list
{
    void *data;
    struct list *next;
};

struct list *list_init(void *ptr);
void list_add(struct list *list, void *ptr);
void *list_get_n(struct list *list, size_t n);


#endif /* LIST_H */
