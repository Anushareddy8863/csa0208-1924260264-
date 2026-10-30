/*
 Task 4: Redesigned smart-meter billing with configurable time-of-day tariff.
 Input readings.csv: one interval per line: hour,watt_hours
 Example: 17,250 ; 18,500 ; 22,250
 tariff.cfg contains:
 fixed_charge_paise=3000
 normal_rate_paise_per_kwh=450
 peak_percent=120
 Peak period is 18:00-21:59 (6 PM inclusive to 10 PM exclusive).
 Cost is accumulated as integer numerator and rounded once to nearest paisa.
 Compile: gcc -std=c11 -Wall -Wextra task04_smart_meter_tou.c -o task04
 Run: ./task04 [tariff.cfg] [readings.csv]
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#define DEFAULT_CONFIG "tariff.cfg"
#define DEFAULT_READINGS "readings.csv"

typedef struct {
    int64_t fixed_paise;
    int64_t normal_rate_paise_per_kwh;
    int peak_percent;
} Tariff;

static int load_tariff(const char *path, Tariff *t) {
    FILE *fp = fopen(path, "r");
    char line[160], key[80];
    long long value;
    int seen = 0;
    if (!fp) { perror("Cannot open tariff configuration"); return 0; }
    while (fgets(line, sizeof line, fp)) {
        if (sscanf(line, " %79[^=]=%lld", key, &value) != 2) continue;
        if (strcmp(key, "fixed_charge_paise") == 0) {
            t->fixed_paise = value; seen |= 1;
        } else if (strcmp(key, "normal_rate_paise_per_kwh") == 0) {
            t->normal_rate_paise_per_kwh = value; seen |= 2;
        } else if (strcmp(key, "peak_percent") == 0) {
            t->peak_percent = (int)value; seen |= 4;
        }
    }
    fclose(fp);
    return seen == 7 && t->fixed_paise >= 0 &&
           t->normal_rate_paise_per_kwh >= 0 && t->peak_percent >= 100;
}

int main(int argc, char **argv) {
    const char *config = argc > 1 ? argv[1] : DEFAULT_CONFIG;
    const char *readings = argc > 2 ? argv[2] : DEFAULT_READINGS;
    Tariff tariff;
    FILE *fp;
    char line[160];
    int hour;
    unsigned long long wh;
    int64_t numerator = 0, total_paise;
    unsigned long long total_wh = 0;
    unsigned long intervals = 0;

    if (!load_tariff(config, &tariff)) {
        puts("Invalid or incomplete tariff.cfg."); return 1;
    }
    fp = fopen(readings, "r");
    if (!fp) { perror("Cannot open readings file"); return 1; }

    while (fgets(line, sizeof line, fp)) {
        char *p = line;
        while (*p == ' ' || *p == '\t') ++p;
        if (*p == '\0' || *p == '\n' || *p == '#') continue;
        if (sscanf(p, "%d , %llu", &hour, &wh) != 2 || hour < 0 || hour > 23) {
            puts("Invalid reading row. Expected hour,watt_hours."); fclose(fp); return 1;
        }
        /* numerator units: paise * Wh * percentage; divide by 100000 */
        numerator += (int64_t)wh * tariff.normal_rate_paise_per_kwh *
                     ((hour >= 18 && hour < 22) ? tariff.peak_percent : 100);
        total_wh += wh;
        ++intervals;
    }
    fclose(fp);

    /* 1 kWh = 1000 Wh; percentage is /100, hence denominator 100000. */
    total_paise = tariff.fixed_paise + (numerator + 50000) / 100000;
    printf("Intervals processed: %lu\nEnergy: %llu Wh (%.3f kWh)\n",
           intervals, total_wh, total_wh / 1000.0);
    printf("Bill: Rs.%" PRId64 ".%02" PRId64 "\n", total_paise / 100, total_paise % 100);
    puts("Peak window: 18:00-21:59; tariff loaded from configuration file.");
    return 0;
}
