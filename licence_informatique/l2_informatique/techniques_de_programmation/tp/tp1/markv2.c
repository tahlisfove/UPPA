#include<stdio.h>

int main()
{
  int mark;
  printf(" Saisir une note : ");
  scanf("%d", &mark);

  do
  {
    if(mark >= 16 && mark <= 20)
      {
        printf("excellent \n");
      }
    if(mark >= 12 && mark <= 16)
      {
        printf("good \n");
      }
    if(mark >= 10 && mark <= 12)
      {
        printf("satisfactory \n");
      }
    if(mark >= 0 && mark <= 10)
      {
        printf("failing \n");
      }

  } while(getchar() >= 0 && getchar() <= 20 '\n');
  return 0;
}
