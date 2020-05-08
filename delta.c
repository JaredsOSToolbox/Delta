#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "includes/file_struct.h"
#include "includes/paragraph.h"
#include "includes/delta.h"
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

void read_all_args(int argc, const char* argv[]){
  bool is_unknown_flag = false;
  char buffer[20];
  memset(buffer, 0, sizeof(buffer));
  while(argc-- > 0 && !is_unknown_flag){
    set_flags(*argv, "-v", "--version", &version); // done
    set_flags(*argv, "-q", "--brief", &brief); // done
    set_flags(*argv, "-s", "--report-identical-files", &report_identical);
    set_flags(*argv, "", "--normal", &normal);
    set_flags(*argv, "-y", "--side-by-side", &side_by_side);
    set_flags(*argv, "-y", "--left-column", &left_column);
    set_flags(*argv, "-y", "--suppress-common-lines", &suppress_common);
    set_flags(*argv, "-c", "--context", &context);
    set_flags(*argv, "-u", "--unified", &unified);
    if(!version && !brief && !report_identical && !normal && !side_by_side && !left_column && !suppress_common && !context && !unified){ is_unknown_flag = true; strcat(buffer, *argv); }
    ++argv;
  }
  if(is_unknown_flag){
    printf("got an unknown value of %s\n", buffer);
  }
}

int main(int argc, const char* argv[]){
  read_all_args(--argc, ++argv);
  if(version){
    print_version();
    return 0;
  }

  struct file_* a = file_constructor("inputs/test");
  struct file_* b = file_constructor("inputs/test_two");

  int qlast_index = EOF;
  paragraph* qlast;

  bool match = paragraph_network_equal(*a->para_network, *b->para_network);
  printf("these two files are the same: %s", (match) ? "true" : "false");
  return 0;

  if(qlast_index != EOF){ qlast = b->para_network->paragraph_nodes[qlast_index]; }
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
      printf("here is where normal mode comes in\n");
      printf("%s%50s\n", a->file_path, b->file_path);
      print_paragraph_networks(a->para_network, b->para_network);
    }
  }

  file_destructor(a);
  file_destructor(b);
  return 0;
}

