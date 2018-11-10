#include <err.h>
#include "include/list.h"

struct list *list_init(void *ptr)
{
    struct list *new = malloc(sizeof(struct list));
    if (!new)
        return NULL;
    new->data = ptr;
    new->next = NULL;
    return new;
}

void list_add(struct list *list, void *ptr)
{
    warnx("adding to list..");
    while (list->next != NULL)
    {
        warnx("node taken. going to next one..");
        list = list->next;
    }
    struct list *new = list_init(ptr);
    if (!new)
        return;
    list->next = new;
}

void *list_get_n(struct list *list, size_t n)
{
    size_t count = 0;
    while (count < n)
    {
        list = list->next;
        count++;
        if (!list)
        {
            warnx("index specified not found");
            return NULL;
        }
    }
    return list->data;
}
