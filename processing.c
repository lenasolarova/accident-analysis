#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "processing.h"
#include "parser.h"


bool open_file(){
    FILE* file_pointer = fopen("dopravni_nehody_-1895066464895987623.csv", "r");
    if (file_pointer == NULL){
        return EXIT_FAILURE;
    }

    char **header = NULL;
    int ncols = 0;

    char line[2048];

    //get names for columns from first line
    if (fgets(line, sizeof(line), file_pointer)) {
        line[strcspn(line, "\n")] = 0;
        header = parse_one_line(line, &ncols);
    }

    //parse the rest
    while(fgets(line, sizeof(line), file_pointer)){
        line[strcspn(line, "\n")] = 0;
        int ncols;

        char **fields = parse_one_line(line, &ncols);

        for (int i = 0; i < ncols; i++) {
            printf("    [%s] %s\n", header[i], fields[i]);
            free(fields[i]);
        }
        printf("--------------------\n");
        free(fields);
    }
    
    fclose(file_pointer);
    return EXIT_SUCCESS;
}