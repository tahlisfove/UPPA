#include <stdio.h>
#include <stdlib.h>

typedef enum {
   monday, 
   tuesday, 
   wednesday, 
   thursday, 
   friday, 
   saturday, 
   sunday
  }day_t;

  typedef struct {
    char *name;
    char **authors;
    int nauthors;
    char *publisher;
    int year;
    long int isbn;
  }book_t;
  
  typedef struct{
    char *name;
    day_t *days;
    int ndays;
    book_t *books;
    int nbooks;
  }library_t;

  void book_print(book_t book){
    int i=0;
    printf("%s'),", book.name);
    printf("('%s') '", book.authors[i]);
    printf("%s', ", book.publisher);
    printf("%d, " , book.year);
    printf("%ld), ", book.isbn);
  }

  void library_print(library_t lib){
    int i=0;
    char *days[] = {"('monday'", "'tuesday'", "'wednesday'", "'thursday'", 
      "'friday')", "'saturday'", "'sunday'"};
    printf("%s ", lib.name);

    for (i=0; i<lib.ndays; i++){
      printf("%s, ",days[lib.days[i]]);}

    for (i=0; i<lib.nbooks; i++){
     book_print(lib.books[i]);
    }
    printf("%s\n", " ");}

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

  void book_free(book_t* book){
    free(book);}
  void library_free(library_t* lib){
    free(lib);}

  int book_add_author(book_t* book, char* authors){
    book->authors = realloc(book->authors,(book->nauthors+1) * sizeof(char*));
    if(book->authors==NULL){
      return -1;
    }
    book->authors[book->nauthors] = authors;
    book->nauthors++;
    return 0;
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

int main(){
  book_t* ptrb;
  library_t* ptrl;
  ptrb = book_create();
  ptrl = library_create();

  book_add_author(ptrb, "ab");
  library_add_book(ptrl, *ptrb);
  library_add_day(ptrl, monday);

  book_free(ptrb);
  library_free(ptrl);
return 0;
}




















/*
int library_add_book(book_t* book, *livre){
    book->name = realloc(book->name) * sizeof(char);
    book->authors = realloc(book->authors,(book->nauthors+1)) * sizeof(char*);
    book->publisher = realloc(book->publisher) * sizeof(char);
    book->year = realloc(book->year) * sizeof(int);
    book->isbn = realloc(book->isbn) * sizeof(long int);

    if(book->name==NULL && book->authors==NULL && book->publisher==NULL && book->year==0 && book->isbn==0){
      return -1;
    }
    book->name[book->name] = name;
    book->name++;
    book->authors[book->authors] = authors;
    book->authors++;
    book->publisher[book->publisher] = publisher;
    book->publisher++;
    book->year[book->year] = year;
    book->year++;
    book->isbn[book->isbn] = isbn;
    book->isbn++;
    return 0;
  }
*/



/* library_t novel = {
    "('Novel Library',",
    {1, 2, 3, 4},
    4,
    {{"(('Harry Potter and the Philosopher’s Stone", 
       {"J.K. Rowling"}, 
           1, 
            "Bloomsbury", 
               1997, 
                  9780747532699},

     {"('Harry Potter and the Chamber of Secrets", 
        {"J.K. Rowling"}, 
           1, 
            "Bloomsbury", 
              1998, 
                   9780747538493}},
    2,
  };


  library_t science = {
    "('Science Library',",
   {0, 1, 2, 3},
    4,
    {{"(('The C Programming Language", 
        {"Brian W. Kernighan , Dennis M.Ritchie"}, 
          2, 
           "Prentice Hall", 
              1988, 
                9780131103627},

    {"('C: The Complete Reference",
       {"Herbert Schildt"}, 
        1, 
          "McGraw-Hill Education", 
             2000, 
               780072121247}},
    2,
  }; */
