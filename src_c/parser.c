#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "parser.h"
#include "processing.h"


bool open_file(RowHandler handler, void* stats){
    char duplicate_id[75000][20] = {{0}};
    int dup_count = 0;
    
    //file opening
    FILE* file_pointer = 
        fopen("../dopravni_nehody_-1895066464895987623.csv", "r");
    //returning if we can not open the file
    if (file_pointer == NULL){
        return EXIT_FAILURE;
    }

    char** header = NULL;
    int ncols = 0;
    char line[2048];

    //gets names for columns from first line, saves them as a header variable
    if (fgets(line, sizeof(line), file_pointer)) {
        line[strcspn(line, "\n")] = 0;
        header = parse_one_line(line, &ncols);
    }

    //parses the rest of the lines in the file
    while(fgets(line, sizeof(line), file_pointer)){
        line[strcspn(line, "\n")] = 0;
        int ncols;

        //gets the line divided and stored in fields variable
        char **fields = parse_one_line(line, &ncols);

        //chosen handler retrives necessary information
        handler(header, ncols, fields, stats, duplicate_id, &dup_count);

        free(fields);
    }
    
    fclose(file_pointer);
    return EXIT_SUCCESS;
}


//parsing a single line
char** parse_one_line(char* line, int* count) {
    char** fields = malloc(256 * sizeof(char*));
    *count = 0;
    char *pointer = line;

    //until we are at the end of the line
    while(*pointer){
        char field_buffer[1024];
        int current = 0;

        //case one: we find an opening "
        //in this case we can ignore any commas until another " is found
        //as they are a part of the field itself
        if(*pointer == '"'){
            pointer++;

            while(*pointer){
                //closing " found -> moving to a normal comma separated field
                if(*pointer == '"'){
                    pointer++;
                    break;
                }
                //adds the non-separator char into the field_buffer
                else{
                    field_buffer[current++] = *pointer++;
                }
            }
        }
        //case two: normal comma separated fields
        //adds the non-separator chars into the field_buffer
        else{
            while(*pointer && *pointer != ','){
                field_buffer[current++] = *pointer++;
            }
        }

        //ends the string with a null byte
        //copies the now string into the fields array
        field_buffer[current] = '\0';
        fields[(*count)++] = strdup(field_buffer);

        //skipping comma as it is merely a separator
        if (*pointer == ',') pointer++;
    }
    return fields;
}

//finds the index for a column name
int get_col_index(char **header, int ncols, const char *colname) {
    for (int i = 0; i < ncols; i++) {
        if (strcmp(header[i], colname) == 0)
            return i;
    }
    return -1;
}

//checks for duplicates
bool is_duplicate(char duplicate_id[][20], int dup_count, const char *id) {
    for (int i = 0; i < dup_count; i++) {
        if (strcmp(duplicate_id[i], id) == 0) return true;
    }
    return false;
}

//finds accident id, checks if it has been already processed and stores it
bool store_duplicate_id(char **header, int ncols, char duplicate_id[][20], 
                        int *dup_count){

    int id_index = get_col_index(header, ncols, "id_nehody");
    if (id_index < 0) return true; //returns if we cannot check
    
    //returns if the id is duplicate
    if (is_duplicate(duplicate_id, *dup_count, "id_nehody")) return true;

    //stores this accident id in duplicate array for later
    strncpy(duplicate_id[*dup_count], "id_nehody", 19);
    duplicate_id[*dup_count][19] = '\0';
    (*dup_count)++;
    
    return false;
}