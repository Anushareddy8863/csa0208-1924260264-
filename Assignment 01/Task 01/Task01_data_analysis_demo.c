/*
Task 1 - Identify and validate billing data
Note: Task 1 is mainly an analysis task; this small program demonstrates
the main input data and validates the 16-bit meter readings.
*/
#include <stdio.h>
#include <limits.h>

typedef unsigned short meter_t;

int main(void)
{
    char household[30];
    char category[20];
    unsigned int previous, current;

    printf("Enter household number: ");
    if (scanf("%29s", household) != 1) {
        printf("Invalid household number.\n");
        return 1;
    }

    printf("Enter category: ");
    if (scanf("%19s", category) != 1) {
        printf("Invalid category.\n");
        return 1;
    }

    printf("Enter previous reading (0-%u): ", (unsigned)USHRT_MAX);
    if (scanf("%u", &previous) != 1 || previous > USHRT_MAX) {
        printf("Invalid previous reading.\n");
        return 1;
    }

    printf("Enter current reading (0-%u): ", (unsigned)USHRT_MAX);
    if (scanf("%u", &current) != 1 || current > USHRT_MAX) {
        printf("Invalid current reading.\n");
        return 1;
    }

    printf("\nHousehold number: %s\n", household);
    printf("Category: %s\n", category);
    printf("Previous reading: %u\n", previous);
    printf("Current reading: %u\n", current);
    printf("Readings validated successfully.\n");

    return 0;
}
