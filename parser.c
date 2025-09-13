#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "parser.h"
#include "processing.h"

char** parse_one_line(char* line, int* count){
    char** fields = malloc(100 * sizeof(char*));//TODO free
    *count = 0;

    char *token = strtok(line, ",");
    while (token != NULL) {
        fields[*count] = strdup(token);//TODO free
        (*count)++;
        token = strtok(NULL, ",");
    }
    return fields;   
}