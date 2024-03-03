#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/parser_struct.h"

#ifndef FUNC_GREP
#define FUNC_GREP

#define OPTIONS "e:ivclshnf:o"
#define SEPARATOR "\n"
#define M_T 100
#define N_T 800
#define M_F 50
#define N_F 260

parser set_options(int argc, char *argv[], parser stat);
char **memory_alloc(const int m, const int n);
void memory_free(parser stat);
parser get_template(char *argv[], parser stat);
parser rewrite_template(FILE *fp, parser stat, int *all_match);
parser add_file_template(parser stat, int *error, int *all_match);
int noTemplates(parser stat);
void files_processing(FILE *fp, char *argv[], parser stat, int j, int num_files,
                      int all_match);
char *regexp_search(char *template, char *file_line, parser stat,
                    char *res_line);
parser template_separation(parser stat);
void str_output(char *string, char *file_name, parser stat, int num_files,
                int lines_count);
void print_pattern(parser stat);

#endif
