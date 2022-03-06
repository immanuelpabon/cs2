#include <stdio.h>
#include <stdlib.h>
#include "bit_flags.h"

typedef struct bit_flags {
    unsigned int *flag_holder;
    int size;
} Bit_Flags;

void set_flag(unsigned int flag_holder[], int flag_position);
void unset_flag(unsigned int flag_holder[], int flag_position);
int check_flag(unsigned int flag_holder[], int flag_position);
void display_32_flags_as_array(unsigned int flag_holder);
void display_flags(unsigned int flag_holder[], int size); 

// BIT_FLAGS



// private functions
// take an integer and make sure that the nth bit is a 1.
void set_flag(unsigned int flag_holder[], int flag_position) {
    int index = flag_position/(sizeof(int) * 8);
    int position = flag_position%(sizeof(int) * 8);
    flag_holder[index] |= 1 << position;
}


// return an integer that is zero when the nth bit is zero and 1 when it is 1
int check_flag(unsigned int flag_holder[], int flag_position){
    int index = flag_position/(sizeof(int) * 8);
    int position = flag_position%(sizeof(int) * 8);

    if (1 << position & flag_holder[index]) {
        return 1;
    }
    return 0;
}


 //flip flag from 1 to a 0

void unset_flag(unsigned int flag_holder[], int flag_position) {
    int index = flag_position/(sizeof(int) * 8);
    int position = flag_position%(sizeof(int) * 8);
    flag_holder[index] = flag_holder[index]^1 << position;
}


// print 32 flags (same as daily 3)
void display_32_flags_as_array(unsigned int flag_holder){
    int i;
    unsigned int arr[1] = {flag_holder};

    for (i = 0; i < 32; i++) {
        
        printf("%d", check_flag(arr, i));
        if(i%4 == 3) {

            printf(" ");
        }
    }
    printf("\n");
}

void display_flags(unsigned int flag_holder[], int size) {
    int i;
    for (i=0; i<size; i++) {
        display_32_flags_as_array(flag_holder[i]);
    }

}

