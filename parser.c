#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "parser.h"
#include "processing.h"

typedef void (*RowHandler)(char **header, int ncols, char **row, void *userdata, char duplicate_id[75000][20], int *dup_count);

bool open_file(RowHandler handler, void* stats){
    char duplicate_id[75000][20] = {{0}};
    int dup_count = 0;
    
    FILE* file_pointer = fopen("dopravni_nehody_-1895066464895987623.csv", "r");
    if (file_pointer == NULL){
        return EXIT_FAILURE;
    }

    char** header = NULL;
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

        handler(header, ncols, fields, stats, duplicate_id, &dup_count);

        free(fields);
    }
    
    fclose(file_pointer);
    return EXIT_SUCCESS;
}


/*
parsing a single line
cannot use strtok on "," because the set contains
values wrapped in "" that contain a "," inside
*/
char** parse_one_line(char* line, int* count) {
    char** fields = malloc(256 * sizeof(char*));
    *count = 0;
    char *pointer = line;

    while(*pointer){
        char buffer[1024];
        int bufpos = 0;

        //check for opening "
        if(*pointer == '"'){
            pointer++;
            while(*pointer){
                //closing " found -> move to another field
                if(*pointer == '"'){
                    pointer++;
                    break;
                }
                else{
                    buffer[bufpos++] = *pointer++;
                }
            }
        }
        //comma separated text
        else{
            while(*pointer && *pointer != ','){
                buffer[bufpos++] = *pointer++;
            }
        }

        buffer[bufpos] = '\0';
        fields[*count] = strdup(buffer);
        (*count)++;

        //skip comma like strtok would
        if (*pointer == ',') pointer++;
    }
    return fields;
}


int get_col_index(char **header, int ncols, const char *colname) {
    for (int i = 0; i < ncols; i++) {
        if (strcmp(header[i], colname) == 0)
            return i;
    }
    return -1;
}

bool is_duplicate(char duplicate_id[][20], int dup_count, const char *id) {
    for (int i = 0; i < dup_count; i++) {
        if (strcmp(duplicate_id[i], id) == 0) {
            return true;
        }
    }
    return false;
}