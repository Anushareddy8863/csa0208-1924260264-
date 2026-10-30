#include <stdio.h>
#include "billing.h"

long get_units(unsigned short previous, unsigned short current)
{
    return ((long)current - (long)previous + 65536L) % 65536L;
}

long calculate_bill(long units)
{
    long bill = FIXED_CHARGE_PAISE;
    if (units > 100)
        bill += (units < 200 ? units - 100 : 100) * RATE2_PAISE;
    if (units > 200)
        bill += (units - 200) * RATE3_PAISE;
    return bill;
}

int main(void)
{
    unsigned short previous, current;
    long units, bill;
    printf("Enter previous and current readings (0-65535): ");
    if (scanf("%hu %hu", &previous, &current) != 2) {
        printf("Invalid input\n");
        return 1;
    }
    units = get_units(previous, current);
    bill = calculate_bill(units);
#ifdef DEBUG
    printf("DEBUG: Units = %ld\n", units);
    printf("DEBUG: Bill in paise = %ld\n", bill);
#endif
    printf("Units consumed: %ld\n", units);
    printf("Bill: Rs %ld.%02ld\n", bill / 100, bill % 100);
    return 0;
}
