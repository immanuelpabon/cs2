#ifndef _LIST_H
#define _LIST_H
#include <stdbool.h>

struct node {
    struct node *next;
    int data;
};

struct list {
    struct node *head;
    struct node *tail;
    int count;
};

struct list *list_new(void);
int list_enqueue(struct list *self, int value);
int list_serve(struct list *self);
void list_destroy(struct list **pself);
int list_sum(struct list *self);
int list_print(struct list *self);
int list_length(struct list *self);
bool list_is_empty(struct list *self);
int list_copy(struct list *dest, struct list *src);

void list_test(void);


#endif