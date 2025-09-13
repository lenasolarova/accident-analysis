#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "parser.h"
#include "processing.h"

bool parse_parameters(int argc, char *argv[]){
    if (argc == 2){
        if (!strcmp(argv[1], "alcohol")){
            AlcoholStats stats = {0};
            open_file(alcohol_handler, &stats);
            printf("Alcohol-related: %d of %d (%.2f%%)\n",
                stats.alcohol_related,
                stats.total,
                (stats.total > 0 ? (100.0 * stats.alcohol_related / stats.total) : 0));
            return EXIT_SUCCESS;
        }
        else if (!strcmp(argv[1], "days")){
            //call days func
            return EXIT_SUCCESS;
        }
        else if (!strcmp(argv[1], "seatbelt")){
            //call sb func
            return EXIT_SUCCESS;
        }
        else if (!strcmp(argv[1], "time")){
            //call time func
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


