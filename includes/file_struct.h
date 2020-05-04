#pragma once
#include <stdbool.h>
#include "paragraph.h"
struct file_{
  char** contents;
  char* file_path;
  int length;
  paragraph_network* para_network;
  //paragraph** para_map;
};

struct file_* file_constructor(const char*);
void file_destructor(struct file_*);

void print_contents(FILE*, struct file_*, bool);
void print_contents_numbered(FILE*, struct file_*);
void print_contents_normal(FILE*, struct file_*);
void print_contents_side_by_side(FILE* stream, struct file_* a, struct file_* b);

void read_contents(struct file_*);

void repr(struct file_*);
bool compare_contents(struct file_*, struct file_*, char*);
bool is_eq(struct file_*, struct file_*);
bool is_neq(struct file_*, struct file_*);
