#ifndef library
#define library

#include <stdio.h>
#include <stdlib.h>

/*typedef enum day_t;
typedef struct library_t;*/
void library_print(library_t lib);
library_t* library_create();
int library_add_book(library_t* lib, book_t books);
int library_add_day(library_t* lib, day_t days);
void library_free(library_t* lib);

#endif