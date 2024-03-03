#include "func.h"

parser set_options(int argc, char *argv[], parser stat) {
  stat.templates = memory_alloc(M_T, N_T);
  stat.file_temp = memory_alloc(M_F, N_F);
  int option;

  while ((option = getopt(argc, argv, OPTIONS)) != -1) {
    switch (option) {
      case 'e':
        stat.e = 1;
        strcpy(stat.templates[stat.tnum], optarg);
        stat.tnum++;
        break;
      case 'i':
        stat.i = 1;
        break;
      case 'v':
        stat.v = 1;
        break;
      case 'c':
        stat.c = 1;
        break;
      case 'l':
        stat.l = 1;
        break;
      case 'h':
        stat.h = 1;
        break;
      case 's':
        stat.s = 1;
        break;
      case 'n':
        stat.n = 1;
        break;
      case 'f':
        stat.f = 1;
        strcpy(stat.file_temp[stat.filetnum], optarg);
        stat.filetnum++;
        break;
      default:
        break;
    }
  }
  return stat;
}

char **memory_alloc(const int m, const int n) {
  char **matrix = (char **)calloc(m, sizeof(char *));
  for (int i = 0; i < m; i++) matrix[i] = (char *)calloc(n, sizeof(char));

  return matrix;
}

void memory_free(parser stat) {
  for (int i = 0; i < M_F; i++) free(stat.file_temp[i]);
  free(stat.file_temp);

  for (int i = 0; i < M_T; i++) free(stat.templates[i]);
  free(stat.templates);
}

parser get_template(char *argv[], parser stat) {
  for (int i = 0; argv[optind][i] != '\0'; i++)
    stat.templates[0][i] = argv[optind][i];
  stat.tnum++;

  return stat;
}

parser add_file_template(parser stat, int *error, int *all_match) {
  FILE *fp = NULL;
  for (int i = 0; i < stat.filetnum; i++) {
    fp = fopen(stat.file_temp[i], "r");
    if (fp) {
      stat = rewrite_template(fp, stat, all_match);
      fclose(fp);
    } else {
      printf("s21_grep: %s: No such file or directory\n", stat.file_temp[i]);
      *error = 1;
    }
  }

  return stat;
}

int noTemplates(parser stat) {
  return ((stat.tnum + stat.filetnum) == 0) ? 1 : 0;
}

parser rewrite_template(FILE *fp, parser stat, int *all_match) {
  char *temp = NULL, *buffer = (char *)malloc(N_T * sizeof(char));

  while ((temp = fgets(buffer, N_T, fp)) != NULL &&
         !(strlen(temp) == 1 && temp[0] == EOF)) {
    if (temp[0] != '\n') {
      temp = strtok(buffer, "\n");
    } else
      *all_match = 1;
    strcpy(stat.templates[stat.tnum++], temp);
  }
  free(buffer);

  return stat;
}

void files_processing(FILE *fp, char *argv[], parser stat, int j, int num_files,
                      int all_match) {
  fp = fopen(argv[j], "r");
  if (fp) {
    char *res_line = NULL, *buffer = (char *)malloc(N_T * sizeof(char));
    int match_count = 0, lines_count = 1;
    char *temp = buffer;
    while ((temp = fgets(temp, N_T, fp)) != NULL) {
      res_line = NULL;
      int match = 0;
      if (all_match) match = 1;
      for (int i = 0; i < stat.tnum; i++) {
        res_line = regexp_search(stat.templates[i], temp, stat, res_line);
        if (res_line) match = 1;
        if (match == 1 && !stat.v) {
          match_count++;
          if (!stat.c && !stat.l)
            str_output(temp, argv[j], stat, num_files, lines_count);
          break;
        }
      }
      if (stat.v && match == 0) {
        match_count++;
        if (!stat.c && !stat.l)
          str_output(temp, argv[j], stat, num_files, lines_count);
      }
      lines_count++;
    }
    if (stat.c) {
      if (!stat.h && num_files != 1) printf("%s:", argv[j]);
      printf("%d\n", (stat.l && match_count != 0) ? 1 : match_count);
    }
    if (stat.l && match_count != 0) printf("%s\n", argv[j]);
    free(buffer);
    fclose(fp);
  } else if (!stat.s)
    printf("s21_grep: %s: No such file or directory\n", argv[j]);
}

char *regexp_search(char *template, char *file_line, parser stat,
                    char *res_line) {
  regex_t preg;
  int error = 0;
  if (stat.i)
    error = regcomp(&preg, template, REG_EXTENDED | REG_ICASE);
  else
    error = regcomp(&preg, template, REG_EXTENDED);
  if (error == 0) {
    if (regexec(&preg, file_line, 0, 0, 0) == 0) res_line = file_line;
  }
  regfree(&preg);
  return res_line;
}

void str_output(char *string, char *file_name, parser stat, int num_files,
                int lines_count) {
  if (!stat.h && num_files != 1) printf("%s:", file_name);
  if (stat.n) printf("%d:", lines_count);
  printf("%s", string);
  if (string[strlen(string) - 1] != '\n') printf("\n");
}