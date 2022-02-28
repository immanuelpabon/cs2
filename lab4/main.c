#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "my_string.h"


int main(int argc, char* argv[])
{
   MY_STRING a;
   MY_STRING b;
   char c;
   c = 's';
   a = my_string_init_c_string("Lab");
   b = my_string_init_c_string("Four");
   

   my_string_concat(a, b);
   assert(strcmp("LabFour", my_string_c_str(a)) == 0);

   my_string_push_back(a, c);
   assert(strcmp("LabFours", my_string_c_str(a)) == 0);

   my_string_pop_back(a);
   assert(strcmp("LabFour", my_string_c_str(a)) == 0);

   assert(my_string_at(a, 10) == NULL);

   my_string_reset(a);
   assert(my_string_empty(a) == TRUE);


   return 0;
}
