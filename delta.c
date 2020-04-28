#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "includes/file_struct.h"
#include "includes/delta.h"

const char* AUTHOR = "Jared Dyreson";
const char* INSTITUTION = "California State University Fullerton";

void print_version(){
  printf(
    "delta (%s) 1.0\n"
    "Copyright (C) 2020 Free Software Foundation, Inc.\n"
    "License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>."
    "This is free software: you are free to change and redistribute it.\n"
    "There is NO WARRANTY, to the extent permitted by law.\n"
    "Written by %s\n",
  INSTITUTION, AUTHOR); 
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
  struct file_* a = file_constructor("inputs/left.txt");
  struct file_* b = file_constructor("inputs/right.txt");

  if(version){
    print_version();
  } else if(brief || report_identical){
    if(!compare_contents(a, b)){
      printf("Files %s and %s differ\n", a->file_path, b->file_path);
    }
    else{
      printf("Files %s and %s are identical\n", a->file_path, b->file_path);
    }
  } else if(normal){
    printf("this is normal diff!\n");
  }
  file_destructor(a);
  file_destructor(b);
  return 0;
}

