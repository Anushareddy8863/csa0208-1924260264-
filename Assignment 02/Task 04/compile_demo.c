#include <stdio.h>
#define RATE 225

int main(void)
{
    int units = 150;
    int charge = (units - 100) * RATE;
    printf("Energy charge: %d paise\n", charge);
    return 0;
}
