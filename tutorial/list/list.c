#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

struct list *list_new(void) {
    struct list *list;

    list = (struct list *)malloc(sizeof(struct list));

    if (list == NULL) {
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    list->count = 0;

    return list;
}

bool list_is_empty(struct list *self) {

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

void list_destroy(struct list **pself) {

    struct list *list = *pself;
    if(!list_is_empty(list)) {
        node_destroy(list->head);
    }

    free(list);
    *pself = NULL;
}

int list_length(struct list *self) {
    return self->count;
}

int node_sum(struct node *self) {

    if (self->next == NULL) {
        return self->data;
    }

    return self->data + node_sum(self->next);
}

int list_sum(struct list *self) {

    if(list_is_empty(self)) {
        return 0;
    }

    return node_sum(self->head);
}

int list_copy(struct list *dest, struct list *src) {
    
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

int list_enqueue(struct list *self, int value){
    struct node *node;

    node = (struct node *)malloc(sizeof(struct node));

    if (node == NULL) {
        return -1;
    }

    node->data = value;
    node->next = NULL;

    if (list_is_empty(self)) {
        self->head = node;
        self->tail = node;
        self->count = 1;
        return 0;
    }
    // what the tail is pointing too points to the new node
    self->tail->next = node;
    // the tail points to the new node.
    self->tail = node;
    // count++
    self->count++;

    return 0;
}

int list_serve(struct list *self) {

    struct node *node;

    node = self->head;

    self->head = self->head->next;

    int save;
    save = node->data;

    free(node);
    
    self->count--;
    return save;
}


void list_test(void) {
    struct list *list1;

    list1 = list_new();
    assert(list1 != NULL);
    assert(list1->head == NULL);
    assert(list1->tail == NULL);
    assert(list1->count == 0);

    int ret;

    ret = list_sum(list1);
    assert(ret == 0);

    ret = list_enqueue(list1, 10);
    assert(list1->count == 1);
    assert(list1->tail != NULL);
    assert(list1->head != NULL);
    assert(ret == 0);
    assert(list1->head->data == 10);
    assert(list1->tail->data == 10);
    assert(list1->tail->next == NULL);
    
    ret = list_sum(list1);
    assert(ret == 10);

    ret = list_enqueue(list1, 12);
    assert(list1->count == 2);
    assert(list1->tail != NULL);
    assert(list1->head != NULL);
    assert(ret == 0);
    assert(list1->head->data == 10);
    assert(list1->tail->data == 12);
    assert(list1->tail->next == NULL);
    assert(list1->head->next->data == 12);

    ret = list_sum(list1);
    assert(ret == 22);

    ret = list_serve(list1);
    assert(ret == 10);
    assert(list1->count == 1);
    assert(list1->head->data == 12);

    
    ret = list_sum(list1);
    assert(ret == 12);


    list_destroy(&list1);
}
