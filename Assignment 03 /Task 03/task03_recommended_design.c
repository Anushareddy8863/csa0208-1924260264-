/*
 Task 3: Recommended production design.
 Tariff is centralized in one constant table; money is stored as integer paise;
 totals use long long. This version supports a 16-bit meter rollover.
 Fixed charge = Rs.30; slab rates are paise/unit.
 Compile: gcc -std=c11 -Wall -Wextra task03_recommended_design.c -o task03
*/
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

#define METER_MAX UINT32_C(65535)
#define FIXED_PAISE INT64_C(3000)
#define SLAB_COUNT 2

typedef struct {
    uint32_t upper_limit; /* cumulative unit limit */
    int64_t rate_paise;
} Slab;

static const Slab tariff[SLAB_COUNT] = {
    {100, 0}, {200, 225}
};
static const int64_t ABOVE_200_RATE = 450;

static uint64_t units_used(uint32_t old_reading, uint32_t new_reading) {
    if (new_reading >= old_reading) return new_reading - old_reading;
    return (uint64_t)(METER_MAX - old_reading) + 1U + new_reading;
}

static int64_t calculate_bill(uint64_t units) {
    int64_t total = FIXED_PAISE;
    uint64_t remaining = units, lower = 0;
    int i;
    for (i = 0; i < SLAB_COUNT; ++i) {
        uint64_t width = tariff[i].upper_limit - lower;
        uint64_t used = remaining < width ? remaining : width;
        total += (int64_t)used * tariff[i].rate_paise;
        remaining -= used;
        lower = tariff[i].upper_limit;
        if (remaining == 0) break;
    }
    total += (int64_t)remaining * ABOVE_200_RATE;
    return total;
}

int main(void) {
    uint32_t previous, current;
    uint64_t units;
    int64_t amount;
    printf("Enter previous and current readings (0..65535): ");
    if (scanf("%" SCNu32 " %" SCNu32, &previous, &current) != 2 ||
        previous > METER_MAX || current > METER_MAX) {
        puts("Invalid input."); return 1;
    }
    units = units_used(previous, current);
    amount = calculate_bill(units);
    printf("Units: %" PRIu64 "\nBill: Rs.%" PRId64 ".%02" PRId64 "\n",
           units, amount / 100, amount % 100);
    return 0;
}
