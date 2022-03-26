#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node {
    struct node *next;
    char data;
};

struct stack {
    struct node *head;
    struct node *tail;
    int count;
};

struct stack *stack_new(void);
int stack_push(struct stack *self, char value);
char stack_pop(struct stack *self);
void stack_destroy(struct stack **pself);
int stack_is_empty(struct stack *self);
void stack_test(void);
int stack_read(struct stack *self, FILE* fp);
int stack_check(struct stack *self);
void clear_keyboard_buffer(void);


/* prototypes */


/* main program */
int main(int argc, char *argv[]){
    int nlines;
    struct stack *s;
    int i;
    char c;
    int noc;
    
    scanf("%d", &nlines);
    clear_keyboard_buffer();
    for (i=0; i < nlines; i++){
        s = stack_new();

        /* stack_read(s, stdin); */
        noc = scanf("%c", &c);
        while (noc == 1 && c != '\n') {
            stack_push(s, c);
            noc = scanf("%c", &c);
        }
        if(stack_check(s) == 0) {
            printf("No\n");
        }else{
            printf("Yes\n");
        }
        stack_destroy(&s);
    }
    
    return 0;
}

/* stack */
int stack_read(struct stack *self, FILE *fp) {
    char c;
    int status;
    
    do {
        c = fgetc(fp);
    } while (isspace(c) && c != EOF);
    
    if (c == EOF) {
        return -1;
    }

    while (!isspace(c) && c != EOF) {
        status = stack_push(self, c);
        if (status != 0) {
            return status;
        }
        c = fgetc(fp);
    }
    return 0;
}

int stack_check(struct stack *self) {
    struct stack *rights;
    int check = 0;
    rights = stack_new();

    char holder;
    char right;
    do {
        if (stack_is_empty(self)) {
            check = 1;
            break;
        }
        holder = stack_pop(self);

        if (holder == ']' ||
            holder == '}' ||
            holder == ')') {
                stack_push(rights, holder);

        } else if (holder == '[' ||
            holder == '{' ||
            holder == '(') { 

            right = stack_pop(rights);
            if (right == -1) {
                check = 0;
                break;
            }

            if (holder == '[' && right != ']') {
                check = 0;
                break;

            }else if(holder == '{' && right != '}') {
                check = 0;
                break;
            
            }else if(holder == '(' && right != ')') {
                check = 0;
                break;
            }
        }

    } while(1);

    if (!stack_is_empty(rights)) {
        check = 0;
    }

    stack_destroy(&rights);

    return check;
}


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

int stack_is_empty(struct stack *self) {

    if (self->head == NULL) {
        return 1;
    }
    return 0;
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


int stack_push(struct stack *self, char value){
    struct node *node;

    node = (struct node *)malloc(sizeof(struct node));

    if (node == NULL) {
        return -1;
    }

    node->data = value;
    node->next = self->head;

    if (stack_is_empty(self)) {
        self->head = node;
        self->tail = node;
        self->count = 1;
        return 0;
    }
   
    self->head = node;
 
    self->count++;

    return 0;
}

char stack_pop(struct stack *self) {

    struct node *node;

    if (stack_is_empty(self)) {
        return -1;
    }

    node = self->head;

    self->head = self->head->next;

    char save;
    save = node->data;

    free(node);
    
    self->count--;
    return save;
}

void clear_keyboard_buffer(void) {
    char c;
    int noc;
    noc = scanf("%c", &c);
    while(noc == 1 && c != '\n') {
        scanf("%c", &c);
    }
}