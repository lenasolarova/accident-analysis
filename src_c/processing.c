#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "processing.h"
#include "parser.h"


//handler function for alcohol argument
void alcohol_handler(char **header, int ncols, char **row, void *userdata, 
                    char duplicate_id[][20], int *dup_count){

    //initializes the struct
    AlcoholStats *stats = (AlcoholStats*) userdata;

    //decides whether to continue (only when it is not a duplicate)
    //and stores the id for later checks
    if (store_duplicate_id(header, ncols, duplicate_id, dup_count)) return;

    //only continues working with the caused by alcohol (alkohol_vinik) column
    int cause_index = get_col_index(header, ncols, "alkohol_vinik");
    if (cause_index < 0) return;

    //increments the counters for alcohol related accidents and total
    if (!strcmp(row[cause_index], "ano")){
        stats->total++;
        stats->alcohol_related++;
    } 
    else if (!strcmp(row[cause_index], "ne")){
        stats->total++;
    }
}

void days_handler(char **header, int ncols, char **row, void *userdata, 
                char duplicate_id[][20], int *dup_count){

    DayStats *stats = (DayStats*) userdata;

    if (store_duplicate_id(header, ncols, duplicate_id, dup_count)) return;

    //only continues working with the day (den) column which is an int (1 to 7)
    int day_index = get_col_index(header, ncols, "den");
    if (day_index < 0) return;

    //increments the counters for the specific day and total counter
    int day_num = atoi(row[day_index]);
    if (day_num >= 1 && day_num <= 7) {
        stats->day_counts[day_num - 1]++;
        stats->total++;
    }
}

//handler function for seatbelt argument
void seatbelt_handler(char **header, int ncols, char **row, void *userdata,
                      char duplicate_id[][20], int *dup_count){

    SeatbeltStats *stats = (SeatbeltStats*) userdata;

    if (!store_duplicate_id(header, ncols, duplicate_id, dup_count)) return;

    //retrieves indices for necessary columns
    int dui_index = get_col_index(header, ncols, "stav_ridic");
    int seatbelt_index = get_col_index(header, ncols, "ozn_osoba");
    int injury_index = get_col_index(header, ncols, "nasledek");
    int person_index = get_col_index(header, ncols, "osoba");
    if (dui_index < 0 || 
        seatbelt_index < 0 || 
        injury_index < 0 || 
        person_index < 0) return;

    //alcohol is only measured in drivers thus the correlation only
    //make sense for drivers
    if (!strstr(row[person_index], "řidič")) return;

    //saves info about dui (0 = false or 1 = true), similarly about
    //seatbelt usage and finally type of injury received
    int dui = (strstr(row[dui_index], "pod vlivem ")) ? 1 : 0;
    int no_seatbelt = (strstr(row[seatbelt_index], "nepřipoutan")) ? 1 : 0;

    //0: no injuries (bez zraněn)
    //1: minor injuries (lehké zranění)
    //2: severe injuries (těžké zranění)
    //3: fatal accident (usmrcení)
    int injury = -1;
    if (strstr(row[injury_index], "bez zraněn")) injury = 0;
    else if (strstr(row[injury_index], "lehké zranění")) injury = 1;
    else if (strstr(row[injury_index], "těžké zranění")) injury = 2;
    else if (strstr(row[injury_index], "usmrcení")) injury = 3;

    if (injury >= 0) stats->counts[dui][no_seatbelt][injury]++;
}
