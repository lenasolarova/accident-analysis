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

void seatbelt_handler(char **header, int ncols, char **row, void *userdata,
                      char duplicate_id[][20], int *dup_count) {
    SeatbeltStats *stats = (SeatbeltStats*) userdata;

    int dui_idx = get_col_index(header, ncols, "stav_ridic");
    int seatbelt_idx = get_col_index(header, ncols, "ozn_osoba");
    int injury_idx = get_col_index(header, ncols, "nasledek");
    int person_idx = get_col_index(header, ncols, "osoba");
    if (dui_idx < 0 || seatbelt_idx < 0 || injury_idx < 0 || person_idx < 0) return;

    // only drivers
    if (!strstr(row[person_idx], "řidič")) return;

    // duplicate check
    int id_idx = get_col_index(header, ncols, "id_nehody");
    if (id_idx < 0) return;
    if (check_and_store_duplicate(duplicate_id, dup_count, row[id_idx])) return;

    int dui = (strstr(row[dui_idx], "pod vlivem alkoholu") ||
               strstr(row[dui_idx], "pod vlivem drog") ||
               strstr(row[dui_idx], "pod vlivem léků")
               ) ? 1 : 0;

    int no_seatbelt = (strstr(row[seatbelt_idx], "nepřipoutaný") ||
                       strstr(row[seatbelt_idx], "airbag") 
                       ) ? 1 : 0;

    int injury = -1;
    if (strstr(row[injury_idx], "bez zraněn")) injury = 0;
    else if (strstr(row[injury_idx], "lehké zranění")) injury = 1;
    else if (strstr(row[injury_idx], "těžké zranění")) injury = 2;
    else if (strstr(row[injury_idx], "usmrcení")) injury = 3;

    if (injury >= 0) {
        stats->counts[dui][no_seatbelt][injury]++;
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
