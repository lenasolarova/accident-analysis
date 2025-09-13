#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "processing.h"
#include "parser.h"


void alcohol_handler(char **header, int ncols, char **row, void *userdata){
    AlcoholStats *stats = (AlcoholStats*) userdata;
    
    int cause_idx = get_col_index(header, ncols, "alkohol_vinik");
    if (cause_idx < 0) return;

    stats->total++;

    if (strstr(row[cause_idx], "ano")) {
        stats->alcohol_related++;
    }
}

