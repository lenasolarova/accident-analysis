#ifndef PARSER_H
#define PARSER_H

typedef void (*RowHandler)(char **header, int ncols, char **row, void *userdata);


bool open_file(RowHandler handler, void* stats);
char **parse_one_line(char *line, int *count);
int get_col_index(char **header, int ncols, const char *colname);


#endif