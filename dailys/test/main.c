#include <stdio.h>

int main(int argc, char * argv[]) {
    char x;
    x = '3';
    char *s;
    s = &x;

    printf("%c\n", x);
    printf("%c\n", *s);


    return 0;
}