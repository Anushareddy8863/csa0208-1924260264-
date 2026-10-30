/*
Task 4 - Safe macros and static inline functions
*/
#include <stdio.h>

#define RUPEES_TO_PAISE(r) ((long long)(r) * 100LL)
#define SQUARE(x) ((x) * (x))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

static inline int square_int(int x)
{
    return x * x;
}

static inline int max_int(int a, int b)
{
    return (a > b) ? a : b;
}

int main(void)
{
    int a = 3, b = 5;

    printf("Rs 12 -> %lld paise\n", RUPEES_TO_PAISE(12));
    printf("SQUARE(a + 1) = %d\n", SQUARE(a + 1));
    printf("MAX(a, b) = %d\n", MAX(a, b));
    printf("inline square = %d\n", square_int(a + 1));
    printf("inline max = %d\n", max_int(a, b));

    return 0;
}
