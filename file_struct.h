#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define NUMBER_OF_STRINGS 100
#define MAX_STRING_SIZE 200

struct file_{
  char** contents;
  char* file_path;
  int length;
};

void read_contents(struct file_* f);
bool compare_contents(struct file_* a, struct file_* b);

struct file_* file_constructor(const char* file_path){
  struct file_ *f =  (struct file_*)malloc(sizeof(struct file_));
  f->length = 0;
  f->contents = malloc(NUMBER_OF_STRINGS * sizeof(char*));
  f->file_path = malloc(sizeof(char*));
  sprintf(f->file_path, "%s", file_path);
  for (int i = 0; i < NUMBER_OF_STRINGS; i++){
      f->contents[i] = malloc((MAX_STRING_SIZE+1) * sizeof(char));
  }
  read_contents(f);
  return f;
}

void file_destructor(struct file_* f){
  for(int i = 0; i < NUMBER_OF_STRINGS; ++i){
    free(f->contents[i]);
  }
  free(f->contents);
  free(f->file_path);
  free(f);
}

bool __eq__(struct file_* a, struct file_* b){
  bool fn = (strcmp(a->file_path, b->file_path) == 0);  
  bool len = (a->length == b->length);
  bool contents = compare_contents(a, b);
  return (fn && len && contents);
}

bool __neq__(struct file_*a, struct file_* b){
  return !__eq__(a, b);
}

void read_contents(struct file_* f){
  char *line;
  size_t len = 0;
  ssize_t read;
  int line_number_ = 0;

  FILE* file_in = fopen(f->file_path, "r");

  if(file_in == NULL){
    fprintf(stderr, "Could not open file, cowardly refusing!\n");
    file_destructor(f);
    exit(1);
  }

  while ((read = getline(&line, &len, file_in)) != EOF) {
    char* pos;
    if((pos = strchr(line, '\n')) != NULL){ *pos = '\0'; }
    sprintf(f->contents[line_number_], "%s", line);
    line_number_++;
  }
  f->length = line_number_;
}

void print_contents(FILE* stream, struct file_* f){
  for(int i = 0; i < f->length; ++i){
    fprintf(stream, "[%d]: %s", i, f->contents[i]);
  }
}

void print_contents_side_by_side(FILE* stream, struct file_* a, struct file_* b){
  int longest_side_ = (a->length < b->length) ? b->length : a->length;
  int shortest_side_ = (a->length < b->length) ? a->length : b->length;
  char empty[81];
  memset(empty, ' ', 80);
  empty[80] = '\0';
  for(int i = 0; i < longest_side_; ++i){
    char leftside[BUFSIZ], rightside[BUFSIZ], numbered_line[BUFSIZ];
    sprintf(numbered_line, "[%d]: %-75s", (i < shortest_side_) ? i : -1, (i < shortest_side_) ? a->contents[i] : "(null)");
    sprintf(leftside, "%s", (i < shortest_side_) ? numbered_line : empty);
    memset(numbered_line, 0, sizeof(char));
    sprintf(numbered_line, "[%d]: %5s\n", (i < longest_side_) ? i : -1, (i < longest_side_) ? b->contents[i] : "(null)");
    sprintf(rightside, "%s", (i < longest_side_) ? numbered_line : empty);
    fprintf(stream, "%s %s", leftside, rightside);
  }
}

bool compare_contents(struct file_* a, struct file_* b){
  if(a->length != b->length){ return false; }
  for(int i = 0; i < a->length; ++i){
    if(strcmp(a->contents[i], b->contents[i]) != 0){ return false; }
  }
  return true;
}
