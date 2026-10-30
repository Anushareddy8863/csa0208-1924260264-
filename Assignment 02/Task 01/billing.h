#ifndef BILLING_H
#define BILLING_H
#define FIXED_CHARGE_PAISE 5000L
#define RATE2_PAISE 225L
#define RATE3_PAISE 450L
long get_units(unsigned short previous, unsigned short current);
long calculate_bill(long units);
#endif
