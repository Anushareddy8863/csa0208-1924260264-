#include <stdio.h>

int main(void)
{
    unsigned short previous, current;
    long units, bill;
    printf("Enter previous and current readings (0-65535): ");
    if (scanf("%hu %hu", &previous, &current) != 2) {
        printf("Invalid input\n");
        return 1;
    }
    units = ((long)current - (long)previous + 65536L) % 65536L;
    bill = 5000L;
    if (units > 100)
        bill += (units < 200 ? units - 100 : 100) * 225L;
    if (units > 200)
        bill += (units - 200) * 450L;
    printf("Units consumed: %ld\n", units);
    printf("Bill: Rs %ld.%02ld\n", bill / 100, bill % 100);
    return 0;
}
