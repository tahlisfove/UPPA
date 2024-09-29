#include <stdio.h>
#include <stdlib.h>
#include "library.h"

typedef enum {
  monday, tuesday, wednesday, thursday, friday, saturday, sunday
}day_t;

typedef struct{
  char *name;
  day_t *days;
  int ndays;
  book_t *books;
  int nbooks;
}library_t;


void library_print(library_t lib){
 int i=0;
 char *days[] = {"('monday'", "'tuesday'", "'wednesday'", "'thursday'", "'friday')", "'saturday'", "'sunday'"};
  printf("%s ", lib.name);
  for (i=0; i<lib.ndays; i++){
     printf("%s, ",days[lib.days[i]]);}
  for (i=0; i<lib.nbooks; i++){
     book_print(lib.books[i]);
    }
     printf("%s\n", " ");
}
    
library_t* library_create(){
 library_t *ptrl = NULL;
  ptrl = malloc(sizeof(library_t));
  ptrl -> name = NULL;
  ptrl -> days = NULL;
  ptrl -> ndays = 0;
  ptrl -> books = NULL;
  ptrl -> nbooks = 0;
  return ptrl;
}

int library_add_day(library_t* lib, day_t days){
  lib->days = realloc(lib->days,(lib->ndays+1) * sizeof(day_t*));
  if(lib->days==NULL){
    return -1;
  }
  lib->days[lib->ndays] = days;
  lib->ndays++;
  return 0;
}

int library_add_book(library_t* lib, book_t books){
  lib->books = realloc(lib->books,(lib->nbooks+1) * sizeof(book_t*));
  if(lib->books == NULL){
    return -1;
  }
  lib->books[lib->nbooks] = books;
  lib->nbooks++;
    return 0;
  }

void library_free(library_t* lib){free(lib);}
