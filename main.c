#include <stdio.h>
#include "includes/file_struct.h"

int main(int argc, const char* argv[]){
  struct file_* f_a = file_constructor("inputs/left.txt");
  struct file_* f_b = file_constructor("inputs/right.txt");
  print_contents_side_by_side(stdout, f_a, f_b);
  /*print_contents(stdout, f_a);*/
  /*printf("\n");*/
  /*print_contents(stdout, f_b);*/
  file_destructor(f_a);
  file_destructor(f_b);
  return 0;
}
