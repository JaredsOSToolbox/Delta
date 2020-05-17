#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "includes/delta.h"
#include "includes/file_t.h"
#include "includes/paragraph.h"
#include "includes/printer.h"

const char* AUTHOR = "Jared Dyreson";
const char* COAUTHOR = "William McCarthy";
const char* INSTITUTION = "California State University Fullerton";


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

void read_all_args(char** files, int argc, const char* argv[]){
  int c = 0;
  while(argc-- > 0){
    set_flags(*argv, "-v", "--version", &version); // done
    set_flags(*argv, "-q", "--brief", &brief); // done
    set_flags(*argv, "-s", "--report-identical-files", &report_identical);
    set_flags(*argv, "--normal", NULL, &normal);
    set_flags(*argv, "-y", "--side-by-side", &side_by_side);
    set_flags(*argv, "--left-column", NULL,  &left_column);
    set_flags(*argv, "--suppress-common-lines", NULL, &suppress_common);
    set_flags(*argv, "-c", "--context", &context);
    set_flags(*argv, "-u", "--showunified", &unified);
    if(*argv[0] != '-'){ 
      if(c > 2){ fprintf(stderr, "too many files, cowardly refusing!\n"); exit(1); }
      files[c++] = *argv; 
    }
    ++argv;
  }
}

int main(int argc, const char* argv[]){
  char** fs = malloc(2 * sizeof(char*));
  read_all_args(fs, --argc, ++argv);

  if(version){
    print_version();
    return 0;
  }

  file_t* a = file_constructor(*fs++);
  file_t* b = file_constructor(*fs);

  bool match = paragraph_network_equal(a->para_network, b->para_network);

  if(match){
    if(brief || report_identical){
      printf("%sFiles %s and %s are identical%s\n",
              ANSI_COLOR_GREEN, a->file_path, b->file_path, ANSI_COLOR_RESET);
      return 0;
    }
  } else{
    if(brief){
      printf("%sFiles %s and %s differ%s\n",
              ANSI_COLOR_RED, a->file_path, b->file_path, ANSI_COLOR_RESET);
      return 0;
    }
    else{
      printf("%s%50s\n\n\n", a->file_path, b->file_path);
      print_paragraph_networks(a->para_network, b->para_network);
    }
  }

  file_destructor(a);
  file_destructor(b);
  return 0;
}
