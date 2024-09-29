#include <stdio.h>

int main() {
int max;
int i;
    do {
        printf("max: ");
        scanf("%d", &max);
        while(getchar() != '\n');
    } while (max < 0);
for (i = 0; i <= max; i++) {
    printf("%d\n", i);
}
return 0;
}