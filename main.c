#include <stdio.h>
#include "includes/file_struct.h"

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

int main(int argc, const char* argv[]){
  struct file_* f_a = file_constructor("inputs/left.txt");
  struct file_* f_b = file_constructor("inputs/right.txt");
  print_contents_side_by_side_mod(stdout, f_a, f_b);
  /*print_contents(stdout, f_a);*/
  /*printf("\n");*/
  /*print_contents(stdout, f_b);*/
  file_destructor(f_a);
  file_destructor(f_b);
  return 0;
}
