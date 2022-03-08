#include <stdio.h>
#include <stdlib.h>
#include "bit_flags.h"

typedef struct bit_flags {
    unsigned int *flag_holder;
    int size;
    int capacity;
} Bit_Flags;

void set_flag(unsigned int flag_holder[], int flag_position);
void unset_flag(unsigned int flag_holder[], int flag_position);
int check_flag(unsigned int flag_holder[], int flag_position);
void display_32_flags_as_array(unsigned int flag_holder);
void display_flags(unsigned int flag_holder[], int size); 

// BIT_FLAGS

BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits) {
    Bit_Flags* pBitFlags;
    pBitFlags = (Bit_Flags*)malloc(sizeof(Bit_Flags));

    if(pBitFlags != NULL) {
        pBitFlags->size = number_of_bits;
        pBitFlags->capacity = pBitFlags->size/(sizeof(unsigned int)*8) + 1;
        pBitFlags->flag_holder = (unsigned int *)calloc(pBitFlags->capacity, sizeof(unsigned int));
    }

    if(pBitFlags->flag_holder == NULL) {
        free(pBitFlags);
        return NULL;
    }
    return pBitFlags;
}

int bit_flags_get_size(BIT_FLAGS hBit_flags) {
    Bit_Flags *pBitFlags= (Bit_Flags *)hBit_flags;
    return pBitFlags->size;
}

int bit_flags_get_capacity(BIT_FLAGS hBit_flags) {
    Bit_Flags *pBitFlags= (Bit_Flags *)hBit_flags;
    return pBitFlags->capacity * sizeof(unsigned int) * 8;
}

Status bit_flags_resize(BIT_FLAGS hBit_flags, int number_of_bits) {
    Bit_Flags *pBitFlags= (Bit_Flags*)hBit_flags;

    pBitFlags->size = number_of_bits;
    pBitFlags->capacity = pBitFlags->size/(sizeof(unsigned int)*8) + 1;
    pBitFlags->flag_holder = (unsigned int*)realloc(pBitFlags->flag_holder, sizeof(unsigned int) * pBitFlags->capacity);
    if (pBitFlags->flag_holder == NULL) {
        return FAILURE;
    }

    return SUCCESS;
}

Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position) {
    Bit_Flags *pBitFlags= (Bit_Flags *)hBit_flags;
    Status status;

    if (flag_position >= pBitFlags->size) {
        status = bit_flags_resize(hBit_flags, flag_position);
        if (status != SUCCESS) {
            return status;
        }
    }
    set_flag(pBitFlags->flag_holder, flag_position);
    return SUCCESS;
}

Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position) {
    Bit_Flags *pBitFlags= (Bit_Flags *)hBit_flags;
    Status status;

    if (flag_position >= pBitFlags->size) {
       status = bit_flags_resize(hBit_flags, flag_position);
       if (status != SUCCESS) {
           return status;
       }
    }
    unset_flag(pBitFlags->flag_holder, flag_position);
    return SUCCESS;
}

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position) {
    Bit_Flags *pBitFlags = (Bit_Flags *)hBit_flags;
    if (flag_position > pBitFlags->size) {
        return -1;
    }
    return check_flag(pBitFlags->flag_holder, flag_position);
}

void bit_flags_destroy(BIT_FLAGS *phBit_flags) {
    Bit_Flags *pBitFlags = (Bit_Flags *)(*phBit_flags);
    free(pBitFlags->flag_holder);
    free(pBitFlags);
    *phBit_flags = NULL;
}

// private functions
// take an integer and make sure that the nth bit is a 1.
void set_flag(unsigned int flag_holder[], int flag_position) {
    int index = flag_position/(sizeof(unsigned int) * 8);
    int position = flag_position%(sizeof(unsigned int) * 8);
    flag_holder[index] |= 1 << position;
}

// return an integer that is zero when the nth bit is zero and 1 when it is 1
int check_flag(unsigned int flag_holder[], int flag_position){
    int index = flag_position/(sizeof(unsigned int) * 8);
    int position = flag_position%(sizeof(unsigned int) * 8);

    if (1 << position & flag_holder[index]) {
        return 1;
    }
    return 0;
}


 //flip flag from 1 to a 0

void unset_flag(unsigned int flag_holder[], int flag_position) {
    int index = flag_position/(sizeof(unsigned int) * 8);
    int position = flag_position%(sizeof(unsigned int) * 8);
    // flag_holder[index] = flag_holder[index]^1 << position;
    flag_holder[index] &= ~(1<<position);
}


