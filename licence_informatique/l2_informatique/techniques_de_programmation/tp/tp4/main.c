#include <stdio.h>
#include <stdlib.h>

int main(){
  book_t* ptrb;
  library_t* ptrl;
  ptrb = book_create();
  ptrl = library_create();

  book_add_author(ptrb, "abc");
  library_add_book(ptrl, *ptrb);
  library_add_day(ptrl, monday);

  book_free(ptrb);
  library_free(ptrl);
return 0;
}