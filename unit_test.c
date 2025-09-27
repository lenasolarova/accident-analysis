#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "src_c/parser.h"
#include "src_c/processing.h"

void test_alcohol() {
    AlcoholStats stats = {0};
    open_file("test.csv", alcohol_handler, &stats);
    double pct = 100.0 * stats.alcohol_related / stats.total;
    assert((int)pct == 75);
}

void test_days() {
    DayStats stats = {0};
    open_file("test.csv", days_handler, &stats);
    double pct_mon = 100.0 * ((double)stats.day_counts[0] / stats.total);
    double pct_fri = 100.0 * ((double)stats.day_counts[4] / stats.total);
    double pct_sun = 100.0 * ((double)stats.day_counts[6] / stats.total);
    assert((int)pct_mon == 25);
    assert((int)pct_fri == 50);
    assert((int)pct_sun == 25);
}

void test_seatbelt() {
    SeatbeltStats stats = {0};
    open_file("test.csv", seatbelt_handler, &stats);
    int total = 0;
    for (int i = 0; i < 4; i++) total += stats.counts[1][1][i];
    double pct_minor = 100.0 * stats.counts[1][1][1] / total;
    assert((int)pct_minor == 33);
}

int main(){
    test_alcohol();
    test_days();
    test_seatbelt();
    printf("✅ All C tests have passed\n");
    return 0;
}