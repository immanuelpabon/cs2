/** Doublely linked list **/
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

typedef void* LINKEDLIST;

LINKEDLIST linkedlist_init_default(void);

void ll_head_insert(LINKEDLIST hLinkedlist, int item);
void ll_tail_insert(LINKEDLIST hLinkedlist, int item);
void ll_ordered_insert(LINKEDLIST hLinkedlist, int item);
void ll_delete(LINKEDLIST hLinkedlist, int item);
void ll_print(LINKEDLIST hLinkedlist);
void ll_reverse_print(LINKEDLIST hLinkedlist);
void linkedlist_destroy(LINKEDLIST* phLinkedlist);

void ferry_init(struct ferry *self, int size_in_meters);
Status ferry_add_car(struct ferry *self, int car_size);
void ferry_remove_cars(struct ferry *self);
void clear_keyboard_buffer(void);


#define MAXLINE 80

static void usage(char *pname);

int main(int argc, char *argv[]) {
    int ferry_sets;
    char shore[1024];
    int i;
    int j;
    
    
    scanf("%d", &ferry_sets);
    clear_keyboard_buffer();
    for (i=0; i < ferry_sets; i++){

        int ferry_size_in_meters;
        int ncars;
        int car_size;

        scanf("%d %d", &ferry_size_in_meters, &ncars);
        clear_keyboard_buffer();
        printf("Ferry size = %d\n", ferry_size_in_meters);
        printf("Number of cars = %d\n", ncars);

        for (j=0; j<ncars; j++) {

            scanf("%d %s", &car_size, shore);
            clear_keyboard_buffer();

            printf("car size = %d\n", car_size);
            printf("shore = %s\n", shore);
        }
    }
    
    return 0;
}


int main2(int argc, char *argv[])
{
    LINKEDLIST ll = linkedlist_init_default();
    char line[MAXLINE];
    char *p;
    int x;
   

    if (argc > 1 && strcmp(argv[1], "-?") == 0)
        usage(argv[0]);

    while (fgets(line, MAXLINE, stdin)) {
        printf("%s", line); 
        
        if ((p = strchr(line, '#'))) *p = '\0';
        if ((p = strchr(line, '\n'))) *p = '\0';
        p = line;
        while (*p == ' ') p++;
        switch (*p) {
        case 'p':
            ll_print(ll);
            break;
                
        case 'r':
            ll_reverse_print(ll);
            break;
                
        case 'H':
            p = strchr(p, ' ');
            if (!p) {
                printf("ll_head_insert - missing value\n");
                break;
            }
            x = atoi(p);
            ll_head_insert(ll, x);
            break;
                
        case 'T':
            p = strchr(p, ' ');
            if (!p) {
                printf("ll_tail_insert - missing value\n");
                break;
            }
            x = atoi(p);
            ll_tail_insert(ll, x);
            break;
            
         case 'D':
            p = strchr(p, ' ');
            if (!p) {
                printf("ll_delete - missing value\n");
                break;
            }
            x = atoi(p);
            ll_delete(ll, x);
            break;

        case 'I':
            p = strchr(p, ' ');
            if (!p) {
                printf("ll_ordered_insert - missing value\n");
                break;
            }
            x = atoi(p);
            ll_ordered_insert(ll, x);
            break;
 
        default: printf("Unknown command\n");
                
        }
    }

    linkedlist_destroy(&ll);
    
    return EXIT_SUCCESS;
}


static void usage(char *pname)
{
  fprintf(stderr, "Usage: %s\n"
          " Test linkedlist.  Call linkedlist_init_default upon startup and\n"
          " linkedlist_destroy upon exit\n\n"
          "  Accept commands from stdin:\n"
          "    p    ll_print\n"
          "    r    ll_reverse_print\n"
          "    H nn ll_head_insert\n"
          "    T nn ll_tail_insert\n"
          "    D nn ll_delete\n"
          "    I nn ll_ordered_insert\n"
          "\n  Command line arguments:\n"
          "    -?    Display this message\n"
           , pname);
  exit(1);
}



struct node;
typedef struct node Node;

struct node
{
    int data;
    int id;
    Node *next;
    Node *prev;
};

struct linkedlist
{
    Node *head;
    Node *tail;
    int id;
};

typedef struct linkedlist linkedlist;

static Node *new_node(linkedlist *pLinkedlist, int item)
{
    Node *pn = (Node *) malloc(sizeof(Node));

    if (pn != NULL) {
        pn->data = item;
        pn->id = ++(pLinkedlist->id);
        pn->next = NULL;
        pn->prev = NULL;
    }
    return pn;
}


LINKEDLIST linkedlist_init_default(void)
{
    linkedlist *pLinkedlist;
    pLinkedlist = (linkedlist *) malloc(sizeof(linkedlist));

    if (NULL == pLinkedlist) {
        fprintf(stderr, "linkedlist_init_default failed to allocate linkedlist\n");
        return NULL;
    }

    pLinkedlist->head = NULL;
    pLinkedlist->tail = NULL;
    pLinkedlist->id = 0;

    return (LINKEDLIST) pLinkedlist;
}

void ll_head_insert(LINKEDLIST hLinkedlist, int item)
{
    linkedlist *pLinkedlist = (linkedlist *) hLinkedlist;
    Node *pNew = new_node(pLinkedlist, item);

    if (NULL == pNew) {
        fprintf(stderr, "ll_head_insert failed to allocate a new node\n");
        return;
    }

    if (pLinkedlist->head){
        pLinkedlist->head->prev = pNew;
    }
    
    pNew->next = pLinkedlist->head;
    pNew->prev = NULL;
    pLinkedlist->head = pNew;
    if (pLinkedlist->tail == NULL) 
        pLinkedlist->tail = pNew;
    
}

void ll_tail_insert(LINKEDLIST hLinkedlist, int item)
{
    linkedlist *pLinkedlist = (linkedlist *) hLinkedlist;
    Node *pNew = new_node(pLinkedlist, item);

    if (NULL == pNew) {
        fprintf(stderr, "ll_tail_insert failed to allocate a new node\n");
        return;
    }

    if (pLinkedlist->tail)
        pLinkedlist->tail->next = pNew;
    
    pNew->prev = pLinkedlist->tail;
   
    pLinkedlist->tail = pNew;
    if (pLinkedlist->head == NULL) 
        pLinkedlist->head = pNew;
}

void ll_ordered_insert(LINKEDLIST hLinkedlist, int item)
{
    linkedlist *pLinkedlist = (linkedlist *) hLinkedlist;
    Node *pNew = new_node(pLinkedlist, item);
    Node *pNode = pLinkedlist->head;
    

    if (NULL == pNew) {
        fprintf(stderr, "ll_ordered_insert failed to allocate a new node\n");
        return;
    }

    if (NULL == pNode) {
        pLinkedlist->head = pNew;
        pLinkedlist->tail = pNew;
        return;
    }

    while (pNode) {
        if (pNode->data >= item) {     
            if (pNode->prev)
                pNode->prev->next = pNew;
            else
                pLinkedlist->head = pNew;

            pNew->next = pNode;
            pNode->prev = pNew;
            return;
        }
        pNode = pNode->next;
    }

   
    
    pLinkedlist->tail->next = pNew;
    pNew->prev = pLinkedlist->tail;
    pLinkedlist->tail = pNew;
}

void ll_delete(LINKEDLIST hLinkedlist, int item)
{
   
}

void ll_print(LINKEDLIST hLinkedlist)
{
    linkedlist *pLinkedlist = (linkedlist *) hLinkedlist;
    Node *pNode = pLinkedlist->head;

    while (pNode) {
        printf("%p id: %d value: %d\n", pNode, pNode->id, pNode->data);
        pNode = pNode->next;
    }
}

void ll_reverse_print(LINKEDLIST hLinkedlist)
{
    linkedlist *pLinkedlist = (linkedlist *) hLinkedlist;
    Node *pNode = pLinkedlist->tail;

    while (pNode) {
        printf("%p id: %d value: %d\n", pNode, pNode->id, pNode->data);
        pNode = pNode->prev;
    }
}

void linkedlist_destroy(LINKEDLIST* phLinkedlist)
{
    linkedlist *pLinkedlist = (linkedlist *)*phLinkedlist;

    Node *pNode = pLinkedlist->head;
    Node *ptemp;
    
    while (pNode) {
        ptemp = pNode;
        pNode = pNode->next;
        free (ptemp);
    }
    free (pLinkedlist);
    *phLinkedlist = NULL;
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


void clear_keyboard_buffer(void) {
    char c;
    int noc;
    noc = scanf("%c", &c);
    while(noc == 1 && c != '\n') {
        scanf("%c", &c);
    }
}