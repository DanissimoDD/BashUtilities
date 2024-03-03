#include "func.h"

int main(int argc, char *argv[]) {
  if (argc > 2) {
    int error_flag = 0, all_match = 0;
    parser stat = {0};

    stat = set_options(argc, argv, stat);
    if (stat.templates != NULL && stat.file_temp != NULL) {
      if (noTemplates(stat)) {
        stat = get_template(argv, stat);
        optind++;
      } else
        stat = add_file_template(stat, &error_flag, &all_match);

      if (!error_flag && stat.tnum != 0) {
        int num_files = argc - optind;
        for (int i = optind; i < argc; i++) {
          FILE *fp = NULL;
          files_processing(fp, argv, stat, i, num_files, all_match);
        }
      }
      memory_free(stat);
    }
  }
  return 0;
}