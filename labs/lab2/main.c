#include <stdio.h> 
#include <stdlib.h> 
#include "my_string.h" 
 
int main(int argc, char* argv[]) 
{ 
   MY_STRING apple= NULL; 
   MY_STRING app= NULL; 
   apple = my_string_init_c_string("apple");
   app= my_string_init_c_string("app"); 

   printf("left word size: %d\n", my_string_get_size(apple));
   printf("left word capacity: %d\n", my_string_get_capacity(apple));

   printf("right word size: %d\n", my_string_get_size(app));
   printf("right word capacity: %d\n ", my_string_get_capacity(app));


   printf("comparison: %d\n", my_string_compare(apple, app));
 
   my_string_destroy(&apple); 
   my_string_destroy(&app);
 
   return 0; 
} 
