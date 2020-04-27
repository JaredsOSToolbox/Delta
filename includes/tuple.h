#pragma once

#include <stdbool.h>
#include "slist.h"

typedef struct tuple{
  int x, y;
  const char* name;
  slist* bucket;
  bool keep, remove, insert;
} tuple;

//typedef struct keep_tuple{
  //union{
    //struct tuple t;
  //} base;
//} keep_tuple; 

//typedef struct remove_tuple{
  //union{
    //struct tuple t;
  //} base;
//} remove_tuple; 

//typedef struct insert_tuple{
  //union{
    //struct tuple t;
  //} base;
//} insert_tuple;

typedef struct frontier_tuple{
  union{
    struct tuple t;
    int* coordinates;
  } base;
} frontier_tuple;


// constructors

tuple* named_tuple_constructor(int, int, const char*, slist*);

tuple* tuple_constructor(int, int);

void tuple_destructor(int, ...);

void tuple_repr(tuple*);
