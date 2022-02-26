#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"

typedef struct my_string {
    int size;
    int capacity;
    char* data;
} My_String;

MY_STRING my_string_init_default(void) {
    My_String* phMyString;
    phMyString = (My_String*)malloc(sizeof(My_String));
    
    if (phMyString != NULL) {
      phMyString -> size = 0;
      phMyString -> capacity = 7;
      phMyString -> data = (char *)malloc(sizeof(char) * phMyString->capacity);
     
      if (phMyString -> data == NULL) {
          free(phMyString);
          return NULL;
      }
    }
    return phMyString; 
}

void my_string_destroy(MY_STRING* phMy_string) {
    My_String* pMy_string = (My_String*)*phMy_string;
    free(pMy_string -> data);
    free(pMy_string);
    *phMy_string = NULL;

}

MY_STRING my_string_init_c_string(const char* c_string) {
    My_String* phMyString;
    int count = 0;

    while(c_string[count] != '\0') {
        count++;
    }

    phMyString = (My_String*)malloc(sizeof(My_String));

    if(phMyString != NULL) {
        phMyString -> size = count;
        phMyString -> capacity = count+1;
        phMyString -> data = (char *)malloc(sizeof(char) * phMyString->capacity);
         
        if (phMyString -> data == NULL) {
          free(phMyString);
          return NULL;
      }
      strcpy(phMyString->data, c_string);
    }
    return phMyString;
}

int my_string_get_capacity(MY_STRING hMy_string) {
    My_String* pMy_string = (My_String*)hMy_string;
    return pMy_string -> capacity;
}

int my_string_get_size(MY_STRING hMy_string) {
    My_String* pMy_string = (My_String*)hMy_string;
    return pMy_string -> size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string) {
     My_String* pLeft_string = (My_String*)hLeft_string;
     My_String* pRight_string = (My_String*)hRight_string;
    
    if (my_string_get_size(pLeft_string) < my_string_get_size(pRight_string)) {
        return -1;
    } else if (my_string_get_size(pLeft_string) > my_string_get_size(pRight_string)) {
        return 1;
    }
    return 0;
 }


Status my_string_extraction(MY_STRING hMy_string, FILE* fp) {
    Status status;
    char c;

    my_string_reset(hMy_string);

    do {
        c = fgetc(fp);
    } while (isspace(c) && c != EOF);
    
    if (c == EOF) {
        return FAILURE;
    }

    while (!isspace(c) && c != EOF) {
        status = my_string_add_c(hMy_string, c);
        if (status != SUCCESS) {
            return status;
        }
        c = fgetc(fp);
    }
    
    ungetc(c, fp);

    return my_string_add_c(hMy_string, '\0');
 }    


Status my_string_insertion(MY_STRING hMy_string, FILE* fp) {
    My_String* pMy_string = (My_String*)hMy_string;
    fprintf(fp, "%s", pMy_string->data);
    return SUCCESS;
}



Status my_string_add_c(MY_STRING hMy_string, char c) {
    My_String* pMy_string = (My_String*)hMy_string;

    if (pMy_string->size + 1 >= pMy_string->capacity) {
        pMy_string->capacity+=10;
        pMy_string->data = (char*)realloc(pMy_string->data, sizeof(char) * pMy_string->capacity);
        if (pMy_string->data == NULL) {
            return FAILURE;
        }
    }
    
    pMy_string->data[pMy_string->size++] = c;
    return SUCCESS;
}


Status my_string_reset(MY_STRING hMy_string) {
    My_String* pMy_string = (My_String*)hMy_string;

    pMy_string->size = 0;

    return SUCCESS;

}