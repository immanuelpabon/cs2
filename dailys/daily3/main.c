/***********************************************************
Author: <Immanuel Pabon>
Date: <2/4/2021>
Effort: <1 hour>
Purpose: <Code two functions set_flag and check_flag>
***********************************************************/



#include <stdio.h>

void set_flag(int* flag_holder, int flag_position);
int check_flag(int flag_holder, int flag_position);

int main(int argc, char * argv[]) {

    int flag_holder = 0;
    int i;

    set_flag(&flag_holder, 3);
    set_flag(&flag_holder, 16);
    set_flag(&flag_holder, 31);

    for (i = 31; i >= 0; i--) {
        
        printf("%d", check_flag(flag_holder, i));
        if(i%4 == 0) {

            printf(" ");
        }
    }
    printf("\n");
    return 0;
}
// take an integer and make sure that the nth bit is a 1.
void set_flag(int* flag_holder, int flag_position) {
    *flag_holder = *flag_holder | 1 << flag_position;
}

// return an integer that is zero when the nth bit is zero and 1 when it is 1
int check_flag(int flag_holder, int flag_position) {
    if (1 << flag_position & flag_holder) {
        return 1;
    }
    return 0;
}

