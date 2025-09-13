#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "parser.h"
#include "processing.h"

bool parse_parameters(int argc, char *argv[]){
    if (argc == 2){
        if (!strcmp(argv[1], "alcohol")){
            open_file();
            printf("%s\n", "alc");
            return EXIT_SUCCESS;
        }
        else if (!strcmp(argv[1], "days")){
            //call days func
            printf("%s\n", "days");
            return EXIT_SUCCESS;
        }
        else if (!strcmp(argv[1], "seatbelt")){
            //call sb func
            printf("%s\n", "seat");
            return EXIT_SUCCESS;
        }
        else if (!strcmp(argv[1], "time")){
            //call time func
            printf("%s\n", "time");
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


