#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    printf("char: %ld byte(s), %d to %d \n", sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("signed char: %ld byte(s), %d to %d \n", sizeof(signed char), SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char: %ld byte(s), 0 to %d \n", sizeof(unsigned char), UCHAR_MAX);
    printf("short: %ld byte(s), %d to %d \n", sizeof(short), SHRT_MIN, SHRT_MAX);
    printf("unsigned short: %ld byte(s), 0 to %d \n", sizeof(unsigned short), USHRT_MAX);
    printf("int: %ld byte(s), %d to %d \n", sizeof(int), INT_MIN, INT_MAX);
    printf("unsigned int: %ld byte(s), 0 to %d \n", sizeof(unsigned int), UINT_MAX);
    printf("long: %ld byte(s), %ld to %ld \n", sizeof(long), LONG_MIN, LONG_MAX);
    printf("unsigned long: %ld byte(s), 0 to %ld \n", sizeof(unsigned long), ULONG_MAX);
    printf("float: %ld byte(s), %e to %e \n", sizeof(float), FLT_MIN, FLT_MAX);
    printf("double: %ld byte(s), %e to %e \n", sizeof(double), DBL_MIN, DBL_MAX);
    printf("long double: %ld byte(s), %Le to %Le \n", sizeof(long double), LDBL_MIN, LDBL_MAX);
}