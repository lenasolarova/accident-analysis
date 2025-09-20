#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "parser.h"
#include "processing.h"

bool parse_parameters(int argc, char *argv[]){
    const char* day_array[] = {"Monday", "Tuesday", "Wednesday", "Thursday",\
                             "Friday", "Saturday", "Sunday"};

    if (argc == 2){
        if (!strcmp(argv[1], "alcohol")){
            AlcoholStats stats = {0};
            open_file(alcohol_handler, &stats);
            printf("Percentage of accidents directly caused by alcohol:\
                     \n%.2f%%\n",
                100.0 * stats.alcohol_related / stats.total);

            return EXIT_SUCCESS;
        }
        else if (!strcmp(argv[1], "days")){
            DayStats stats = {0};
            open_file(days_handler, &stats);
            printf("\nDays of the week by their respective \
                    percentage of accidents: \n%");
            for (int i = 0; i < 7; i++){
                printf("%s: %.2f%%\n",
                day_array[i],
                100.0 * stats.day_counts[i] / stats.total);
            }
            return EXIT_SUCCESS;
        }
        else if (!strcmp(argv[1], "seatbelt")){
            SeatbeltStats stats;
            memset(&stats, 0, sizeof(stats));
            open_file(seatbelt_handler, &stats);

            print_table(stats);

            return EXIT_SUCCESS;
        }
        else if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")){
            printf("Supported arguments are:\n   alcohol\n   days\n   \
                    seatbelt\n   time\n");
            return EXIT_SUCCESS;
        }
        else{
            fprintf(stderr, "Invalid option\n");
            printf("Supported arguments are:\n   alcohol\n   days\n   \
                    seatbelt\n   time\n");
            return EXIT_FAILURE;
        }
    }
    fprintf(stderr, "Invalid number of arguments");
    return EXIT_FAILURE;
}

//separate function to print the injury table
void print_table(SeatbeltStats stats){
    const char *injury_names[] = {"none", "minor", "severe", "fatal"};

    //printing a header for the table
    printf("%-10s %-11s", "dui", "no_seatbelt");
    for (int i = 0; i < 4; i++) {
        printf(" %7s", injury_names[i]);
    }
    printf("\n");

    //printing all 4 combinations (rows) of DUI and seatbelts usage
    for (int dui = 0; dui < 2; dui++) {
        for (int no_seatbelt = 0; no_seatbelt < 2; no_seatbelt++) {
            int total = 0;
            for (int i = 0; i < 4; i++){
                total += stats.counts[dui][no_seatbelt][i];
            }

            // row label
            printf("%-10s %-11s",
                dui ? "True" : "False",
                no_seatbelt ? "True" : "False");

            if (total == 0) {
                for (int i = 0; i < 4; i++) printf(" %7s", "NaN");
                printf("\n");
                continue;
            }

            //print percentages
            for (int i = 0; i < 4; i++) {
                double percentage = (
                    100.0 * 
                    stats.counts[dui][no_seatbelt][i] / 
                    total);
                printf(" %7.2f", percentage);
            }
            printf("\n");
        }
    }
}

int main(int argc, char *argv[]){
    parse_parameters(argc, argv);

    return EXIT_SUCCESS;
}

