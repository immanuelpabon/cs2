#ifndef BIT_FLAGS_H
#define BIT_FLAGS_H

#include "status.h"

typedef void* BIT_FLAGS;

Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position);
Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position);
int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position);
BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits);
int bit_flags_get_size(BIT_FLAGS hBit_flags);
int bit_flags_get_capacity(BIT_FLAGS hBit_flags);

#endif // BIT_FLAGS_H