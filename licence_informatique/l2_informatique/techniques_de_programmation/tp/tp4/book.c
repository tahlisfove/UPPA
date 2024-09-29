#include <stdio.h>
#include <stdlib.h>
#include "book.h"

typedef struct {
  char *name;
  char **authors;
  int nauthors;
  char *publisher;
  int year;
  long int isbn;
}book_t;

void book_print(book_t book){
  int i=0;
  printf("%s'),", book.name);
  printf("('%s') '", book.authors[i]);
  printf("%s', ", book.publisher);
  printf("%d, " , book.year);
  printf("%ld), ", book.isbn);
}

book_t* book_create(){
  book_t *ptrb = NULL;
  ptrb = malloc(sizeof(book_t));
  ptrb -> name = NULL;
  ptrb -> authors = NULL;
  ptrb -> nauthors = 0;
  ptrb -> publisher = NULL;
  ptrb -> year = 0;
  ptrb -> isbn = 0;
  return ptrb;
}

int book_add_author(book_t* book, char* authors){
  book->authors = realloc(book->authors,(book->nauthors+1) * sizeof(char*));
  if(book->authors==NULL){
    return -1;
  }
  book->authors[book->nauthors] = authors;
  book->nauthors++;
  return 0;
}

void book_free(book_t* book){free(book);}