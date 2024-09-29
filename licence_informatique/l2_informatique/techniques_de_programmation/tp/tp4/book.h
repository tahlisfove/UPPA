#ifndef book
#define book

#include <stdio.h>
#include <stdlib.h>

typedef struct book_t;
void book_print(book_t book);
book_t* book_create();
void book_free(book_t* book);
int book_add_author(book_t* book, char* authors);

#endif