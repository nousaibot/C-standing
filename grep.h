#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Размеры строковых массивов
#define BUFSIZE 10000
#define ARGBUF 500

typedef struct {
  int e, i, v, c, l, n, h, s, o, f, countFiles, countMatches;
  char e_arg[ARGBUF], f_filename[ARGBUF], pattern[BUFSIZE];
} flags;

void parser(flags *options, int argc, char **argv);

void construct_f_template(flags *options);

void output(flags options, char *filename);

void print_match(flags *options, char *filename, char *source, int num);


void argtest(flags options);
void print_lastchar(char *source);
void substr(char *source, int length);
void prints_snum(int num);

#endif
