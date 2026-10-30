/*
 Task 2: Compare float totals with integer-paise totals and inspect type ranges.
 Assumed representative household bill = Rs.480.00 (48,000 paise):
 250 units + Rs.30 fixed charge under the Task 1 tariff.
 Compile: gcc -std=c11 -Wall -Wextra task02_type_experiment.c -o task02
*/
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void) {
    const long long bill_paise = 48000LL;
    const float bill_rupees = 480.00f;
    const int counts[] = {4000, 60000, 800000};
    int i;

    printf("Type sizes and limits on this system:\n");
    printf("char=%zu (%d..%d)\n", sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("int=%zu (%d..%d)\n", sizeof(int), INT_MIN, INT_MAX);
    printf("long=%zu (%ld..%ld)\n", sizeof(long), LONG_MIN, LONG_MAX);
    printf("long long=%zu (%lld..%lld)\n", sizeof(long long), LLONG_MIN, LLONG_MAX);
    printf("float=%zu (FLT_DIG=%d), double=%zu (DBL_DIG=%d)\n\n",
           sizeof(float), FLT_DIG, sizeof(double), DBL_DIG);

    puts("Households | float rupee total | exact paise total | int fits? | long fits? | long long fits?");
    for (i = 0; i < 3; ++i) {
        long long exact = (long long)counts[i] * bill_paise;
        float ftotal = (float)counts[i] * bill_rupees;
        printf("%9d | Rs.%14.2f | %16lld | %-9s | %-10s | %s\n",
               counts[i], ftotal, exact,
               exact <= INT_MAX ? "yes" : "NO",
               exact <= LONG_MAX ? "yes" : "NO",
               exact <= LLONG_MAX ? "yes" : "NO");
    }
    printf("\nMinimum C guarantees: int >= 16 bits, long >= 32 bits, "
           "long long >= 64 bits; float/double precision is implementation-dependent.\n");
    puts("No overflowing signed integer operation is performed; capacity is checked first.");
    return 0;
}
