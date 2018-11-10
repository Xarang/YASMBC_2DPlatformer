#ifndef LIST_H
#define LIST_H

struct list
{
    void *data;
    struct list *next;
}

struct list *list_init(void *ptr);
void list_add(void *ptr);

#endif /* LIST_H */
