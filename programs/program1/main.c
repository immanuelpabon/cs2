#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "bit_flags.h"

int main (int argc, char *argv[]) {
    BIT_FLAGS test;
    int size;
    int capacity;
    Status set;
    int check;
    Status unset;

    test = bit_flags_init_number_of_bits(80);
    assert(test != NULL);
    
    size = bit_flags_get_size(test);
    assert(size == 80);

    capacity = bit_flags_get_capacity(test);
    assert(capacity == 3*8*sizeof(unsigned int));

    set = bit_flags_set_flag(test, 70);
    assert(set == SUCCESS);
    set = bit_flags_set_flag(test, 90);
    assert(set == SUCCESS);
    set = bit_flags_unset_flag(test, 76);
    assert(set == SUCCESS);

    check = bit_flags_check_flag(test, 70);
    assert(check == 1);
    check = bit_flags_check_flag(test, 90);
    assert(check == 1);
    check = bit_flags_check_flag(test, 76);
    assert(check == 0);
    check = bit_flags_check_flag(test, 92);
    assert(check == -1);

    unset = bit_flags_unset_flag(test, 70);
    assert(unset == SUCCESS);
    unset = bit_flags_unset_flag(test, 100);
    assert(unset == SUCCESS);

    check = bit_flags_check_flag(test, 70);
    assert(check == 0);
    check = bit_flags_check_flag(test, 100);
    assert(check == 0);
    check = bit_flags_check_flag(test, 101);
    assert(check == -1);



    return 0;
}