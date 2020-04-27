#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../includes/tuple.h"
#include "../includes/slist.h"

tuple* named_tuple_constructor(int x, int y, const char* message, slist* bucket){
  tuple* t = (tuple*)malloc(sizeof(tuple*));
  t->x = x;
  t->y = y;
  t->name = strdup(message);
  t->bucket = bucket;
  return t;
}

void tuple_setter(tuple* t, int x, int y, const char* name){
  t->x = x;
  t->y = y;
  t->name = strdup(name);
  t->bucket = slist_create();
}

void tuple_destructor(int count, ...){
  printf("calling %s\n", __func__);
  // https://stackoverflow.com/questions/10071186/function-with-unknown-number-of-parameters-in-c
  // How to pass in an unspecified amount of arguments to C function
  va_list list;
  va_start(list, count);
  for(int i = 0; i < count; ++i){
    printf("%d\n", i);
    tuple* t = va_arg(list, tuple*);
    slist_clear(t->bucket);
    free(t->bucket);
    free(t);
  }
}

void tuple_repr(tuple* t){
  printf("%s: (%d, %d): ", t->name, t->x, t->y);
  slist_print(t->bucket, "tuple_repr");
  printf("\n");
}
