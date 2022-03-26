#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"


void node_destroy(struct node *self);
struct node *node_copy(struct node *head_dest, struct node *head_src);


struct stack *stack_new(void) {
    struct stack *stack;

    stack = (struct stack *)malloc(sizeof(struct stack));

    if (stack == NULL) {
        return NULL;
    }

    stack->head = NULL;
    stack->tail = NULL;
    stack->count = 0;

    return stack;
}

bool stack_is_empty(struct stack *self) {

    if (self->head == NULL) {
        return true;
    }
    return false;
}

void node_destroy(struct node *self) {

    if (self->next != NULL) {
        node_destroy(self->next);
    }

    free(self);
}

void stack_destroy(struct stack **pself) {

    struct stack *stack = *pself;
    if(!stack_is_empty(stack)) {
        node_destroy(stack->head);
    }

    free(stack);
    *pself = NULL;
}

int stack_length(struct stack *self) {
    return self->count;
}

int node_sum(struct node *self) {

    if (self->next == NULL) {
        return self->data;
    }

    return self->data + node_sum(self->next);
}

int stack_sum(struct stack *self) {

    if(stack_is_empty(self)) {
        return 0;
    }

    return node_sum(self->head);
}

int stack_copy(struct stack *dest, struct stack *src) {
    
    dest->head = node_copy(dest->head, src->head);

    return 0;
}

struct node *node_copy(struct node *head_dest, struct node *head_src) {
    if(head_src == NULL) {
        return NULL;
    }

    if(head_dest == NULL) {
        head_dest = (struct node *)malloc(sizeof(struct node));

        if (head_dest == NULL) {
            return NULL;
        }
    }

    head_dest->data = head_src->data;
    head_dest->next = node_copy(head_dest->next, head_src->next);

    return head_dest;
}

int stack_enqueue(struct stack *self, int value){
    struct node *node;

    node = (struct node *)malloc(sizeof(struct node));

    if (node == NULL) {
        return -1;
    }

    node->data = value;
    node->next = NULL;

    if (stack_is_empty(self)) {
        self->head = node;
        self->tail = node;
        self->count = 1;
        return 0;
    }
 
    self->tail->next = node;
   
    self->tail = node;
 
    self->count++;

    return 0;
}

int stack_serve(struct stack *self) {

    struct node *node;

    node = self->head;

    self->head = self->head->next;

    int save;
    save = node->data;

    free(node);
    
    self->count--;
    return save;
}


void stack_test(void) {
    struct stack *stack1;

    stack1 = stack_new();
    assert(stack1 != NULL);
    assert(stack1->head == NULL);
    assert(stack1->tail == NULL);
    assert(stack1->count == 0);

    int ret;

    ret = stack_sum(stack1);
    assert(ret == 0);

    ret = stack_enqueue(stack1, 10);
    assert(stack1->count == 1);
    assert(stack1->tail != NULL);
    assert(stack1->head != NULL);
    assert(ret == 0);
    assert(stack1->head->data == 10);
    assert(stack1->tail->data == 10);
    assert(stack1->tail->next == NULL);
    
    ret = stack_sum(stack1);
    assert(ret == 10);

    ret = stack_enqueue(stack1, 12);
    assert(stack1->count == 2);
    assert(stack1->tail != NULL);
    assert(stack1->head != NULL);
    assert(ret == 0);
    assert(stack1->head->data == 10);
    assert(stack1->tail->data == 12);
    assert(stack1->tail->next == NULL);
    assert(stack1->head->next->data == 12);

    ret = stack_sum(stack1);
    assert(ret == 22);

    ret = stack_serve(stack1);
    assert(ret == 10);
    assert(stack1->count == 1);
    assert(stack1->head->data == 12);

    
    ret = stack_sum(stack1);
    assert(ret == 12);


    stack_destroy(&stack1);
}
