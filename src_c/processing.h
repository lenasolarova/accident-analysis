#ifndef PROCESSING_H
#define PROCESSING_H

//calculates percentage of all accidents caused by alcohol
void alcohol_handler(char** header, int ncols, char** row, void *userdata, 
                    char duplicate_id[5000][20], int *dup_count);

typedef struct {
    int total;
    int alcohol_related;
} AlcoholStats;


//calculates percentage of all accidents per day of the week
void days_handler(char** header, int ncols, char** row, void *userdata, 
                char duplicate_id[5000][20], int *dup_count);

typedef struct {
    int total;
    int day_counts[7];
} DayStats;


//calculates relation between severity of injuries and wearing a seatbelt
//while under the influence
void seatbelt_handler(char** header, int ncols, char** row, void *userdata, 
                    char duplicate_id[5000][20], int *dup_count);

typedef struct {
    //counts[dui][seatbelt][injury]
    int counts[2][2][4];
} SeatbeltStats;

//printer function for the seatbelt function
void print_table(SeatbeltStats stats);

#endif