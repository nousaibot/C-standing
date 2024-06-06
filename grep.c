#include "s21_grep.h"

int main(int argc, char *argv[]) {
  flags opts = {0};
  parser(&opts, argc, argv);

  if (!opts.e && !opts.f) {
    strcat(opts.pattern, argv[optind]);
    optind += 1;
  }
  opts.countFiles = argc - optind;

  for (int i = optind; i < argc; i++){
    output(opts, argv[i]);
  }
  return 0;
}

void print_match(flags*opts, char *filename, char *source, int num) {
  regex_t regex;
  regmatch_t pmatch[1000];
  int regcomp_status = regcomp(&regex, opts->pattern, opts->i ? REG_ICASE | REG_EXTENDED : REG_EXTENDED);
  if (!(regcomp_status)) {
    int regex_status = regexec(&regex, source, 0, NULL, 0);
    if (regex_status == opts->v) {
      opts->countMatches += 1;
      if (!opts->c && !opts->l) {
        if (opts->countFiles > 1 && !(opts->h) && !(opts->o)) {
          printf("%s:", filename);
        }
        if (opts->n && !(opts->o)) {
          prints_snum(num);
          printf(":");
        }
        char *ps = source;
        while (regexec(&regex, ps, 1, pmatch, 0) == 0) {
          if (opts->countFiles > 1 && !(opts->h) && opts->o) {
            printf("%s:", filename);
          }
          if (opts->n && opts->o) {
            prints_snum(num);
            printf(":");
          }
          int pos = pmatch[0].rm_so;  // начало совпадения
		  
          if (pos >= 0 && !opts->o) substr(ps, pos);
          if (pos == 0 && opts->o) substr(ps, pos);
          ps += pos;
          substr(ps, pmatch[0].rm_eo - pos);
          if (opts->o) printf("\n");
          ps -= pos;
          ps += pmatch[0].rm_eo;
        }
        if (!opts->o) {
          printf("%s", ps);  // Допечатка строки
          print_lastchar(ps);
        }
      }
    }
  }
  regfree(&regex);
}

void construct_f_pattern(flags *opts) {
  FILE *f = fopen(optarg, "r");
  char line[BUFSIZE];
  if (f != NULL) {
    while (fgets(line, BUFSIZE, f) != NULL) {
      if (line[strlen(line) - 1] == '\n' && strlen(line) - 1 != '\0') {
        line[strlen(line) - 1] = '\0';
      }
      strcat(opts->pattern, line);
      strcat(opts->pattern, "|");
    }
    opts->pattern[strlen(opts->pattern) - 1] = '\0';
  } else {
    fprintf(stderr, grep: %s: No such file or directory\n, optarg);
    exit(0);
  }
  fclose(f);
}

void parser(flags *opts, int argc, char **argv) {
  for (int sym = 0; (sym = getopt(argc, argv, "e:ivclnhsf:o")) != (-1);) {
    switch (sym) {
      case 'f':
        opts->f = 1;
        strcat(opts->f_filename, optarg);
        construct_f_pattern(opts);
        break;
      case 'e':
        opts->e = 1;
        strcat(opts->e_arg, optarg);
        strcat(opts->e_arg, "|");
        break;
      case 'l':
        opts->l = 1;
        break;
      case 'c':
        opts->c = 1;
        break;
      case 'o':
        opts->o = 1;
        break;
      case 'i':
        opts->i = 1;
        break;
      case 'v':
        opts->v = 1;
        break;
      case 's':
        opts->s = 1;
        break;
      case 'n':
        opts->n = 1;
        break;
      case 'h':
        opts->h = 1;
        break;
      default:
        fprintf(stderr, "no options");
        exit(0);
    }
  }
  if (opts->e) {
    if (opts->e_arg[strlen(opts->e_arg) - 1] == '|')
      opts->e_arg[strlen(opts->e_arg) - 1] = '\0';
    if (opts->f) {
      strcat(opts->pattern, "|");
    }
    strcat(opts->pattern, opts->e_arg);
  }
}

void output(flags opts, char *filename){
  opts.countMatches = 0;
  FILE *f = fopen(filename, "rt");
  if (f != NULL) {
    char line[500] = {0};
    int num = 0;
    while (fgets(line, sizeof(line), f)) {
      num++;
      print_match(&opts, filename, line, num);
    }
    if (opts.c && !opts.l) {
      if (opts.countFiles > 1 && !(opts.h)) {
        printf("%s:", filename);
      }
      printf("%d\n", opts.countMatches);
    }
    if (opts.countMatches > 0) {
      if (opts.l) {
         printf("%s\n", filename);
      }
    }
    fclose(f);
  } else {
    if (opts.countFiles > 1 && opts.l)
      fprintf(stderr, "grep: option requires an argument -- 'e'\nUsage: grep [OPTION]... PATTERNS [FILE]...\nTry 'grep --help' for more information.\n", filename);
  }
}

void print_lastchar(char *source) {
  char lastchar = source[strlen(source) - 1];
  if (lastchar != '\n') printf("\n");
}

void substr(char *source, int length) {
  for (int i = 0; i < length; i++) printf("%c", source[i]);
}

void prints_snum(int num) {
  printf("%d", num);
}
