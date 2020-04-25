#include <stdio.h>
#include <stdlib.h>
#include "includes/file_struct.h"
#include "includes/slist.h"
#include "includes/tuple.h"

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

void meyers_diff(struct file_* a, struct file_* b){
  bool go_down = false;

  char** a_lines = a->contents;
  char** b_lines = b->contents;

  size_t a_max = a->length;
  size_t b_max = b->length;

  int x, y;

  int* frontier_keys = (int*)malloc(sizeof(int)*a_max);
  frontier_tuple* frontier_values = (frontier_tuple*)malloc(sizeof(frontier_tuple)*a_max);

  for(int d = 0; d < (a_max+b_max+1); ++d){
    for(int k = -d; k < d+1; k+=2){
      printf("d: %d, k: %d\n", d, k);
      /*go_down = ((k == -d) || */
                /*(k != d) && (f))*/
      if(go_down){
      }
    }
  }
  free(frontier_keys);
  free(frontier_values);
}

void test_tuples(){
  frontier_tuple a;
  tuple_setter(&a.base.t, 1000, 0, "Frontier");
  printf("%d\n", a.base.t.x);
  printf("%s\n", a.base.t.name);
  slist_pushback(a.base.t.bucket, "Hello");
  slist_print(a.base.t.bucket, "test insertion");
}

int main(int argc, const char* argv[]){
  struct file_* a = file_constructor("inputs/left.txt");
  struct file_* b = file_constructor("inputs/right.txt");
  /*meyers_diff(a, b);*/
  /*tuple_repr(&k->t);*/
  /*tuple_destructor(4, keep, insert, remove, frontier);*/
  file_destructor(a);
  file_destructor(b);
  return 0;

}

