#include <stdio.h>

int main(void)
{
    int a = 5, b = 2;
    double x = 0.1 + 0.2;
    long large = 3000000000L;
    int narrowed = (int)large;
    long bill_paise = 5000L + 50L * 225L;

    printf("Integer division: %d\n", a / b);
    printf("Floating sum: %.17f\n", x);
    printf("After cast to int: %d\n", narrowed);
    printf("Bill: Rs %ld.%02ld\n", bill_paise / 100, bill_paise % 100);
    return 0;
}
