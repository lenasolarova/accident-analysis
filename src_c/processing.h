#ifndef PROCESSING_H
#define PROCESSING_H

bool check_and_store_duplicate(char duplicate_id[][20], int *dup_count, const char *id);

void alcohol_handler(char** header, int ncols, char** row, void *userdata, char duplicate_id[5000][20], int *dup_count);

typedef struct {
    int total;
    int alcohol_related;
} AlcoholStats;

void days_handler(char** header, int ncols, char** row, void *userdata, char duplicate_id[5000][20], int *dup_count);

typedef struct {
    int total;
    int day_counts[7];
} DayStats;

#endif