/***********************************************************
Author: <Immanuel>
Date: <1/28/2021>
Effort: <45 minutes>
Purpose: <Using left shift to print in a loop>
***********************************************************/


#include <stdio.h>

int main(int argc, char * arv[]) {
    unsigned int x = 1;

    for (int i = 0; x != 0; i++) {
        printf("%d: %d\n", i, x);
        x = x << 1;
    }

    return 0;
}