/***********************************************************
Author: Immanuel Pabon
Date: 4/1/2022
Effort: 4 hours
Purpose: Ferry some boats using a link list
***********************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum status { FAILURE, SUCCESS };
typedef enum status Status;

enum boolean { FALSE = 0, TRUE = 1};
typedef enum boolean Boolean;

struct ferry {
    int size;
    int used_size;
};

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
int list_print(struct list *self);
int list_length(struct list *self);
int list_peek(struct list *self);
Boolean list_is_empty(struct list *self);
void ferry_init(struct ferry *self, int size_in_meters);
Status ferry_add_car(struct ferry *self, int car_size);
void ferry_remove_cars(struct ferry *self);
Boolean ferry_check_size(struct ferry *self, int car_size);
Boolean ferry_is_empty(struct ferry *self);
void clear_keyboard_buffer(void);


int main(int argc, char *argv[]) {
    int ferry_sets;
    char shore[1024];
    int i;
    int j;
    struct ferry f;
    
    scanf("%d", &ferry_sets);
    clear_keyboard_buffer();
    for (i=0; i < ferry_sets; i++){
        struct list *ll_left = list_new();
        struct list *ll_right = list_new();
        int ferry_size_in_meters;
        int ncars;
        int car_size;

        scanf("%d %d", &ferry_size_in_meters, &ncars);
        clear_keyboard_buffer();
        printf("Ferry size = %d\n", ferry_size_in_meters);
        printf("Number of cars = %d\n", ncars);

        ferry_init(&f, ferry_size_in_meters);

        /*
         * initialize the shores
         */
        for (j=0; j<ncars; j++) {

            scanf("%d %s", &car_size, shore);
            clear_keyboard_buffer();
            
            if (strcmp(shore, "left")==0) {
                list_enqueue(ll_left, car_size);
            } else {
                list_enqueue(ll_right, car_size);
            }

            printf("car size = %d\n", car_size);
            printf("shore = %s\n", shore);
        }

        /*
         * simulate the ferry
         */
        int counter = 0;

        while(!list_is_empty(ll_left) || !list_is_empty(ll_right)) {

            /*
             * starting on the left
             */
            while (!list_is_empty(ll_left) && 
                ferry_check_size(&f, list_peek(ll_left)) == TRUE) {

                ferry_add_car(&f, list_serve(ll_left));
            }

            if(ferry_is_empty(&f) && list_is_empty(ll_right)) {
                break;
            }
            counter++;
            ferry_remove_cars(&f);

            while (!list_is_empty(ll_right) && 
                ferry_check_size(&f, list_peek(ll_right)) == TRUE) {
                
                ferry_add_car(&f, list_serve(ll_right));
            }

            if(ferry_is_empty(&f) && list_is_empty(ll_left)) {
                break;
            }
            counter++;
            ferry_remove_cars(&f);
        }
        
        printf("%d\n", counter);
        list_destroy(&ll_left);
        list_destroy(&ll_right);

    }
    
    return 0;
}

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

Boolean list_is_empty(struct list *self) {

    if (self->head == NULL) {
        return TRUE;
    }
    return FALSE;
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
   
    self->tail->next = node;
    self->tail = node;
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

int list_peek(struct list *self) {
    if(list_is_empty(self)) {
        return -1;
    }
    return self->head->data;
}

void ferry_init(struct ferry *self, int size_in_meters) {
    self->size = size_in_meters * 100;
    self->used_size = 0;
}

Status ferry_add_car(struct ferry *self, int car_size){
    if (self->used_size + car_size > self->size) {
        return FAILURE;
    } 

    self->used_size += car_size;
    return SUCCESS;
}

void ferry_remove_cars(struct ferry *self){
    self->used_size = 0;
}

Boolean ferry_check_size(struct ferry *self, int car_size) {
    if (self->used_size + car_size > self->size) {
        return FALSE;
    }
    return TRUE;
}

Boolean ferry_is_empty(struct ferry *self) {
    if (self->used_size == 0) {
        return TRUE;
    }
    return FALSE;
}

void clear_keyboard_buffer(void) {
    char c;
    int noc;
    noc = scanf("%c", &c);
    while(noc == 1 && c != '\n') {
        scanf("%c", &c);
    }
}