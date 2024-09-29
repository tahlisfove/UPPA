#include <stdio.h>

int main() {
int bank;
int b5=0,b10=0,b20=0,b50=0,b100=0,b200=0,b500=0;
while(1){ 
    printf("banknote: ");
    scanf("%d", &bank);
    switch(bank)
    {
    case 5 : b5++; break;
    case 10 : b10++; break;
    case 20 : b20++; break;
    case 50 : b50++; break;
    case 100 : b100++; break;
    case 200 : b200++; break;
    case 500 : b500++; break;
    case -1 : printf("exit \n"); return 0; break;
    default : fprintf(stderr, "invalid bank value\n");
}

printf("%d bankote(s) of 5 euros\n", b5);
printf("%d bankote(s) of 10 euros\n", b10);
printf("%d bankote(s) of 20 euros\n", b20);
printf("%d bankote(s) of 50 euros\n", b50);
printf("%d bankote(s) of 100 euros\n", b100);
printf("%d bankote(s) of 200 euros\n", b200);
printf("%d bankote(s) of 500 euros\n", b500);
}
return 0;
}