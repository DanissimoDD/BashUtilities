#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/parser_struct.h"

#ifndef CAT_FUNC
#define CAT_FUNC

parser parser_func(char *str, parser stat);
void file_print(char *str[], int argc, int count, parser stat);
int word_check(char c);
void v_func(char c);
void str_number(int *count);
int isControlChar(int c);

#endif