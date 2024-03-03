#include "cat_func.h"

parser parser_func(char *str, parser stat) {
  if (strcmp(str, "--number-nonblank") == 0)
    stat.b = 1;
  else if (strcmp(str, "--number") == 0)
    stat.n = 1;
  else if (strcmp(str, "--squeeze-blank") == 0)
    stat.s = 1;
  else {
    for (int i = 1; str[i] != '\0'; i++) {
      if (str[i] == 'b')
        stat.b = 1;
      else if (str[i] == 's')
        stat.s = 1;
      else if (str[i] == 'T')
        stat.t = 1;
      else if (str[i] == 'n')
        stat.n = 1;
      else if (str[i] == 'E')
        stat.e = 1;
      else if (str[i] == 't') {
        stat.t = 1;
        stat.v = 1;
      } else if (str[i] == 'e') {
        stat.e = 1;
        stat.v = 1;
      } else {
        stat.no = 1;
        break;
      }
    }
  }
  return stat;
}

int word_check(char c) { return c == '-' ? 1 : 0; }

void file_print(char *str[], int argc, int count, parser stat) {
  int f_count = argc - count, c, row;
  FILE *fp = NULL;

  for (int i = 0; i < f_count; i++, count++) {
    row = 0;
    if ((fp = fopen(str[count], "r")) != NULL) {
      int flag = 0;
      int prev = '\n';
      while ((c = fgetc(fp)) != EOF) {
        if (prev == '\n') {
          if (c == '\n' && stat.s) {
            if (flag) {
              continue;
            }
            flag = 1;
          } else
            flag = 0;
          if (stat.b && c != '\n' && prev == '\n')
            str_number(&row);
          else if (stat.n && !stat.b && prev == '\n')
            str_number(&row);
        }
        if (c == '\n' && stat.e)
          putchar('$');
        else if (c == '\t' && stat.t)
          printf("^I");
        else if (stat.v && isControlChar(c))
          v_func(c);
        if ((stat.t && c == '\t') || (stat.v && isControlChar(c)))
          ;
        else if (c != EOF && putchar(c) == EOF)
          break;
        prev = c;
      }
      fclose(fp);
    } else
      printf("NO SUCH FILE %s", str[count]);
  }
}

void v_func(char c) {
  if (c != 9 && c != 10) printf("^%c", (c + 64) % 128);
}

void str_number(int *count) { printf("%6d\t", ++(*count)); }

int isControlChar(int c) {
  return ((c < 32 || c == 127) && !(c == 9 || c == 10)) ? 1 : 0;
}