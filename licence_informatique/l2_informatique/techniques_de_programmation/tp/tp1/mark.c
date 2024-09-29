#include <stdio.h>

int main() {
int note;
    while (note < 0 || note > 20) {
        printf("mark:");
        scanf("%d", &note);
        while(getchar() != '\n');
    }
    if (note < 10) {
        printf("failing\n");
    }
    else if (note < 12) {
        printf("satisfactory\n");
    }
    else if (note < 16) {
        printf("good\n");
    }
    else printf("excellent\n");
 return 0;
}