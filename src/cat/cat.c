#include "../common/parser_struct.h"
#include "cat_func.h"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    parser stat = {0};
    int i = 1;
    while (word_check(argv[i][0])) {
      stat = parser_func(argv[i], stat);
      i++;
    }
    if (stat.no != 1)
      file_print(argv, argc, i, stat);
    else
      printf("%s: illegal option", argv[0]);
  }
  return 0;
}