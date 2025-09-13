#ifndef PROCESSING_H
#define PROCESSING_H

void alcohol_handler(char** header, int ncols, char** row, void *userdata);

typedef struct {
    int total;
    int alcohol_related;
} AlcoholStats;

#endif