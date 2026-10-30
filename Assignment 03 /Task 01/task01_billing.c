/*
 Task 1: Rural electricity billing
 Assumptions: fixed charge = Rs.30; first 100 units free;
 next 100 units at Rs.2.25/unit; units above 200 at Rs.4.50/unit.
 A 16-bit meter rolls over after 65535.
 Compile: gcc -std=c11 -Wall -Wextra task01_billing.c -o task01
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define METER_MAX 65535U
#define FIXED_CHARGE_PAISE 3000LL

static int read_u32(const char *prompt, unsigned int *value) {
    char line[100], extra;
    char *end;
    unsigned long n;
    printf("%s", prompt);
    if (!fgets(line, sizeof line, stdin)) return 0;
    if (line[0] == '-' || (isspace((unsigned char)line[0]) == 0 && !isdigit((unsigned char)line[0])))
        return 0;
    n = strtoul(line, &end, 10);
    if (end == line || (*end != '\n' && *end != '\0') || sscanf(end, " %c", &extra) == 1 || n > METER_MAX)
        return 0;
    *value = (unsigned int)n;
    return 1;
}

static unsigned long long consumed(unsigned int previous, unsigned int current) {
    if (current >= previous) return current - previous;
    return (unsigned long long)(METER_MAX - previous) + 1ULL + current;
}

static long long bill_paise(unsigned long long units) {
    long long energy = 0;
    if (units > 100) {
        unsigned long long slab2 = units > 200 ? 100 : units - 100;
        energy += (long long)slab2 * 225;
    }
    if (units > 200) energy += (long long)(units - 200) * 450;
    return FIXED_CHARGE_PAISE + energy;
}

int main(void) {
    unsigned int prev, curr;
    unsigned long long units;
    long long paise;
    if (!read_u32("Previous meter reading (0-65535): ", &prev) ||
        !read_u32("Current meter reading (0-65535): ", &curr)) {
        puts("Invalid input: enter whole-number readings from 0 to 65535.");
        return 1;
    }
    if (curr < prev && prev < 60000U) {
        puts("Invalid reading: decrease is not a valid meter rollover.");
        return 1;
    }
    units = consumed(prev, curr);
    paise = bill_paise(units);
    printf("Units consumed: %llu\n", units);
    printf("Bill: Rs.%lld.%02lld\n", paise / 100, paise % 100);
    return 0;
}
