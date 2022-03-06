#include <stdio.h>
#include <stdlib.h>


int main(int argc, char **argv) {
    char x;
    char *s;
    char w[4];
    char y;

    x = 'h';
    s = &x;

    printf("x at 0x%x\n",(unsigned int)&x); //printing the address of x
    printf("s at 0x%x\n",(unsigned int)&s); //printing the address of s
    
    printf("****\n");

    printf("w at 0x%x\n",(unsigned int)&w);
    printf("w0 at 0x%x\n",(unsigned int)&w[0]); //w[0] and w are the same, because
    printf("w1 at 0x%x\n",(unsigned int)&w[1]); //in memory it is basically
    printf("w2 at 0x%x\n",(unsigned int)&w[2]); //add 0 to the address of w
    printf("w3 at 0x%x\n",(unsigned int)&w[3]);

    printf("***s*\n");

    printf("x has %c - %d\n", (unsigned int)x, x); //printing what's inside of x
    printf("s has 0x%x\n", (unsigned int)s); //printing what's inside of s
    
    return 0;
}