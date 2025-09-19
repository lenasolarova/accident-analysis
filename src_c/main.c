#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "parser.h"
#include "processing.h"

bool parse_parameters(int argc, char *argv[]){
    const char* day_array[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

    if (argc == 2){
        if (!strcmp(argv[1], "alcohol")){
            AlcoholStats stats = {0};
            open_file(alcohol_handler, &stats);
            printf("Percentage of accidents directly caused by alcohol: \n%.2f%%\n",
                100.0 * stats.alcohol_related / stats.total);
            return EXIT_SUCCESS;
        }
        else if (!strcmp(argv[1], "days")){
            DayStats stats = {0};
            open_file(days_handler, &stats);
            printf("\nDays of the week by their respective percentage of accidents: \n%");
            for (int i = 0; i < 7; i++){
                printf("%s: %.2f%%\n",
                day_array[i],
                100.0 * stats.day_counts[i] / stats.total);
            }
            return EXIT_SUCCESS;
        }
        else if (!strcmp(argv[1], "seatbelt")){
            //call sb func
            return EXIT_SUCCESS;
        }
        else if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")){
            printf("Supported arguments are:\n   alcohol\n   days\n   seatbelt\n   time\n");
            return EXIT_SUCCESS;
        }
        else{
            fprintf(stderr, "Invalid option\n");
            printf("Supported arguments are:\n   alcohol\n   days\n   seatbelt\n   time\n");
            return EXIT_FAILURE;
        }
    }
    fprintf(stderr, "Invalid number of arguments");
    return EXIT_FAILURE;
}

int main(int argc, char *argv[]){
    parse_parameters(argc, argv);

    return EXIT_SUCCESS;
}


