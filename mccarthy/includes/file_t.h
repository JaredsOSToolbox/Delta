#pragma once
#include <stdbool.h>
#include "paragraph.h"
typedef struct file_t{
  char** contents;
  char* file_path;
  int length;
  paragraph_network* para_network;
} file_t;

file_t* file_constructor(const char*);
void file_destructor(file_t*);

void print_contents(FILE*, file_t*, bool);
void print_contents_numbered(FILE*, file_t*);
void print_contents_normal(FILE*, file_t*);
void print_contents_side_by_side(FILE* stream, file_t* a, file_t* b);

void read_contents(file_t*);

void repr(file_t*);
bool compare_contents(file_t*, file_t*, char*);
bool is_eq(file_t*, file_t*);
bool is_neq(file_t*, file_t*);
