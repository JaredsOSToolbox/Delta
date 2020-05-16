//
//  diff_02.c
//  diff
//
//  Created by William McCarthy on 4/29/19.
//  Copyright © 2019 William McCarthy. All rights reserved.

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "includes/delta.h"
#include "includes/para.h"
#include "includes/util.h"

void print_version(){
  printf(
    "delta (%s) 1.0\n"
    "Copyright (C) 2020 Free Software Foundation, Inc.\n"
    "License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>."
    "This is free software: you are free to change and redistribute it.\n"
    "There is NO WARRANTY, to the extent permitted by law.\n"
    "Written by %s and %s\n",
  INSTITUTION, AUTHOR, COAUTHOR); 
}

void set_flags(const char* cli_arg, const char* flag, const char* long_flag, bool* value){
  if((strcmp(cli_arg, flag) == 0) || ((long_flag) && strcmp(cli_arg, long_flag) == 0)){
    *value = true;
  }
}

char buf[BUFLEN];
char *strings1[MAXSTRINGS], *strings2[MAXSTRINGS];
bool showversion = false, showbrief = false, ignorecase = false, report_identical = false, showsidebyside = false;
bool showleftcolumn = false, showunified = false, showcontext = false, suppresscommon = false, diffnormal = false;

int count1 = 0, count2 = 0;

int cnt = 0;

file_t *a, *b;


void loadfiles(const char* filename1, const char* filename2) {
  memset(buf, 0, sizeof(buf));
  memset(strings1, 0, sizeof(strings1));
  memset(strings2, 0, sizeof(strings2));
  
  FILE *fin1 = openfile(filename1, "r");
  FILE *fin2 = openfile(filename2, "r");
  
  while (!feof(fin1) && fgets(buf, BUFLEN, fin1) != NULL) { strings1[count1++] = strdup(buf); }  fclose(fin1);
  while (!feof(fin2) && fgets(buf, BUFLEN, fin2) != NULL) { strings2[count2++] = strdup(buf); }  fclose(fin2);
}

void print_option(const char* name, int value) { 
  printf("%17s: %s\n", name, (value == 1) ? "yes" : "no"); 
}

void diff_output_conflict_error(void) {
  fprintf(stderr, "diff: conflicting output style options\n");
  fprintf(stderr, "diff: Try `diff --help' for more information.)\n");
  exit(CONFLICTING_OUTPUT_OPTIONS);
}

void setoption(const char* arg, const char* s, const char* t, int* value) {
  if ((strcmp(arg, s) == 0) || ((t != NULL && strcmp(arg, t) == 0))) {
    *value = 1;
  }
}

void showoptions(const char* file1, const char* file2) {
  printf("diff options...\n");
  print_option("diffnormal", diffnormal);
  print_option("show_version", showversion);
  print_option("show_brief", showbrief);
  print_option("ignorecase", ignorecase);
  print_option("report_identical", report_identical);
  print_option("show_sidebyside", showsidebyside);
  print_option("show_leftcolumn", showleftcolumn);
  print_option("suppresscommon", suppresscommon);
  print_option("showcontext", showcontext);
  print_option("show_unified", showunified);
  
  printf("file1: %s,  file2: %s\n\n\n", file1, file2);
  
  printline();
}

void read_all_args(int argc, const char* argv[]){
  bool is_unknown_flag = false;
  const char* files[2] = { NULL, NULL };
  while(argc-- > 0){
    set_flags(*argv, "-v", "--version", &showversion); // done
    set_flags(*argv, "-q", "--brief", &showbrief); // done
    set_flags(*argv, "-s", "--report-identical-files", &report_identical);
    set_flags(*argv, "-i", "--ignore-case", &ignorecase);
    set_flags(*argv, "", "--normal", &diffnormal);
    set_flags(*argv, "-y", "--side-by-side", &showsidebyside);
    set_flags(*argv, "-y", "--left-column", &showleftcolumn);
    set_flags(*argv, "-y", "--suppress-common-lines", &suppresscommon);
    set_flags(*argv, "-c", "--context", &showcontext);
    set_flags(*argv, "-u", "--unified", &showunified);
    if (*argv[0] != '-') {
      if (cnt == 2) {
        fprintf(stderr, "apologies, this version of diff only handles two files\n");
        fprintf(stderr, "Usage: ./diff [options] file1 file2\n");
        exit(TOOMANYFILES_ERROR);
      } else { files[cnt++] = *argv; }
    }
    ++argv;
  }

  if (!showcontext && !showunified && !showsidebyside && !showleftcolumn) {
    diffnormal = true;
  }

  if (report_identical) { printf("The files are identical.\n");   exit(0); }

  if (showbrief) { printf("The files are different.\n");   exit(0); }

  if (((showsidebyside || showleftcolumn) && (diffnormal || showcontext || showunified)) ||
      (showcontext && showunified) || (diffnormal && (showcontext || showunified))) {

    diff_output_conflict_error();
  }
  printf("loading: %s and %s\n", files[0], files[1]);
  a = file_constructor(files[0]);
  b = file_constructor(files[1]);
  /*loadfiles(files[0], files[1]);*/

}


int main(int argc, const char * argv[]) {
  read_all_args(--argc, ++argv);

  if(showversion){
    print_version();
    exit(0);
  }
  return 0;

  para* p = para_first(strings1, count1);
  para* q = para_first(strings2, count2);

  /*file_t* a = file_constructor(files[0]);*/
  /*file_t* b = file_constructor(files[1]);*/

  return 0;

  /*int foundmatch = 0;*/

  /*para* qlast = q;*/
  /*while (p != NULL) {*/
    /*qlast = q;*/
    /*foundmatch = 0;*/
    /*while (q != NULL && (foundmatch = para_equal(p, q)) == 0) {*/
      /*q = para_next(q);*/
    /*}*/
    /*q = qlast;*/

    /*if (foundmatch) {*/
      /*while ((foundmatch = para_equal(p, q)) == 0) {*/
        /*para_print(q, printright);*/
        /*q = para_next(q);*/
        /*qlast = q;*/
      /*}*/
      /*para_print(q, printboth);*/
      /*p = para_next(p);*/
      /*q = para_next(q);*/
    /*} else {*/
      /*para_print(p, printleft);*/
      /*p = para_next(p);*/
    /*}*/
  /*}*/
  /*while (q != NULL) {*/
    /*para_print(q, printright);*/
    /*q = para_next(q);*/
  /*}*/

  /*return 0;*/
}
