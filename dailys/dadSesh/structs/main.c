#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NAME 512

#define COLOR_UNKNOWN 0
#define COLOR_BROWN 1
#define COLOR_WHITE 2
#define COLOR_GRAY 3

struct dad {
    int age;
    char name[MAX_NAME];
    int beardcolor;
    bool hair;
};
int dad_print(struct dad *self);

int main (int argc, char **argv){
    
    struct dad a;
    dad_print(&a);
    return 0;
}

int dad_print(struct dad *self) {
    if (self == NULL) {
        return -1;
    }
    printf("Name: %s\n", self->name);

    printf("Hair: %d\n", self->hair);
    printf("Age: %d\n", self->age);

    char *color = "Uknown";
    switch(self->beardcolor) {
        case COLOR_BROWN:
            color = "Brown";
            break;
        case COLOR_WHITE:
            color = "White";
            break;
        case COLOR_GRAY:
            color = "White";
            break;
    }
    printf("Beard Color: %s\n", self->beardcolor);
    return 0;
}