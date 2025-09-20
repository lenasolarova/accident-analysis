#ifndef PARSER_H
#define PARSER_H

//generic function for handling different arguments
typedef void (*RowHandler)(char **header, int ncols, char **row, void *userdata, 
                            char duplicate_id[75000][20], int *dup_count);

//function for opening the csv file and parsing through it based on 
//the handler it is called with
bool open_file(RowHandler handler, void* stats);

//function for parsing one line of a CSV file containing text wrapped in ""
//that contains commas inside (unable to use simple strtok)
char **parse_one_line(char *line, int *count);

//returns an index for a column name or -1 if it is not found
int get_col_index(char **header, int ncols, const char *colname);

//checks whether the value has been encountered before
bool is_duplicate(char duplicate_id[][20], int dup_count, const char *id);

//finds the accident id, checks if it has been already processed and stores it
bool store_duplicate_id(char **header, int ncols, char duplicate_id[][20], 
                        int *dup_count);

#endif