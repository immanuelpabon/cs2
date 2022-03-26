#ifndef _STACK_H
#define _STACK_H
#include <stdbool.h>

struct node {
    struct node *next;
    int data;
};

struct stack {
    struct node *head;
    struct node *tail;
    int count;
};

struct stack *stack_new(void);
int stack_enqueue(struct stack *self, int value);
int stack_serve(struct stack *self);
void stack_destroy(struct stack **pself);
int stack_sum(struct stack *self);
int stack_print(struct stack *self);
int stack_length(struct stack *self);
bool stack_is_empty(struct stack *self);
int stack_copy(struct stack *dest, struct stack *src);

void stack_test(void);


#endif