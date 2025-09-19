#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "processing.h"
#include "parser.h"


void alcohol_handler(char **header, int ncols, char **row, void *userdata, char duplicate_id[][20], int *dup_count){
    AlcoholStats *stats = (AlcoholStats*) userdata;

    int cause_idx = get_col_index(header, ncols, "alkohol_vinik");
    if (cause_idx < 0) return;

    int id_idx = get_col_index(header, ncols, "id_nehody");
    if (id_idx < 0) return;
    if (check_and_store_duplicate(duplicate_id, dup_count, row[id_idx])) {
        return;
    }

    char* cause = row[cause_idx];

    if (!strcmp(cause, "ano")){
        stats->total++;
        stats->alcohol_related++;
    } 
    else if (!strcmp(cause, "ne")){
        stats->total++;
    }
}


void days_handler(char **header, int ncols, char **row, void *userdata, char duplicate_id[][20], int *dup_count){
    DayStats *stats = (DayStats*) userdata;

    int day_idx = get_col_index(header, ncols, "den");
    if (day_idx < 0) return;

    int id_idx = get_col_index(header, ncols, "id_nehody");
    if (id_idx < 0) return;
    if (check_and_store_duplicate(duplicate_id, dup_count, row[id_idx])) {
        return;
    }

    int day_num = atoi(row[day_idx]);
    if (day_num >= 1 && day_num <= 7) {
        stats->day_counts[day_num - 1]++;
        stats->total++;
    }
}

bool check_and_store_duplicate(char duplicate_id[][20], int *dup_count, const char *id) {
    //returns if this is duplicate
    if (is_duplicate(duplicate_id, *dup_count, id)) {
        return true;
    }

    //stores this accident id in duplicate array for later
    if (*dup_count < 75000) {
        strncpy(duplicate_id[*dup_count], id, 19);
        duplicate_id[*dup_count][19] = '\0';
        (*dup_count)++;
    }
    return false;
}
