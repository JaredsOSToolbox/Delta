#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../includes/file_t.h"
#include "../includes/paragraph.h"
#include "../includes/printer.h"
// this is a quick change to test if Make will compile!

#define NUMBER_OF_STRINGS 1000
#define MAX_STRING_SIZE 1000
#define PADDING_SIZE 76
#define NUMBER_OF_PARAGRAPHS 500


file_t* file_constructor(const char* file_path){
  file_t *f =  (file_t*)malloc(sizeof(file_t));
  f->contents = malloc(NUMBER_OF_STRINGS * sizeof(char*));
  f->file_path = malloc(sizeof(char*));
  sprintf(f->file_path, "%s", file_path);
  f->para_network = paragraph_network_constructor();
  read_contents(f);
  f->para_network->file_size = f->length;
  slice(f);
  return f;
}

void file_destructor(file_t* f){
  for(int i = 0; i < NUMBER_OF_STRINGS; ++i){
    free(f->contents[i]);
  }
  paragraph_network_destructor(f->para_network);
  free(f->contents);
  free(f->file_path);
  free(f);
  f = NULL;
}

bool is_eq(file_t* a, file_t* b){
  char* message = (char*)malloc(sizeof(char)*BUFSIZ);
  bool fn = (strcmp(a->file_path, b->file_path) == 0);  
  bool len = (a->length == b->length);
  bool contents = compare_contents(a, b, message);
  free(message);
  return (fn && len && contents);
}

bool is_neq(file_t*a, file_t* b){ return !is_eq(a, b); }

void repr(file_t* f){
  printf("Path: %s\n", f->file_path);
  printf("File length: %d\n", f->length);
  printf("Contents of file: \n");
  print_contents(stdout, f, false);
}


// member functions

void read_contents(file_t* f){
  char *line;
  char* pos;
  size_t len = 0;
  ssize_t read;
  int line_number_ = 0, paragraph_index = 0, paragraph_start = 0, paragraph_end = 0;

  FILE* file_in = fopen(f->file_path, "r");

  if(file_in == NULL){
    fprintf(stderr, "Could not open file, cowardly refusing!\n");
    file_destructor(f);
    exit(1);
  }
  
  while ((read = getline(&line, &len, file_in)) != EOF) {
    /*if((pos = strchr(line, '\n')) != NULL){ *pos = '\0'; }*/
    f->contents[line_number_] = malloc((strlen(line)+1) * sizeof(char));
    sprintf(f->contents[line_number_], "%s", line);
    line_number_++;
  }
  f->length = line_number_;
}

void print_contents(FILE* stream, file_t* f, bool numbered){
  char buffer[BUFSIZ];
  for(int i = 0; i < f->length; ++i){
    sprintf(buffer, "[%d]: ", i);
    fprintf(stream, "%s%s", (numbered) ? buffer : "", f->contents[i]);
  }
}

void print_contents_numbered(FILE* stream, file_t* f){
  print_contents(stream, f, true);
}

void print_contents_normal(FILE* stream, file_t* f){
  print_contents(stream, f, false);
}


bool compare_contents(file_t* a, file_t* b, char* message){
  char buffer[BUFSIZ];
  if(a->length != b->length){ 
    sprintf(message, "%sFiles %s(%d) and %s(%d) differ in length, delta of %d lines %s\n",
            ANSI_COLOR_RED, a->file_path, a->length, b->file_path, b->length, abs(a->length-b->length), ANSI_COLOR_RESET);
    return false; 
  }
  for(int i = 0; i < a->length; ++i){
    if(strcmp(a->contents[i], b->contents[i]) != 0){ 
      sprintf(message, ">%s%s[%d]: -> %s%s\n", 
              ANSI_COLOR_RED, a->file_path, i, a->contents[i], ANSI_COLOR_RESET);
      sprintf(buffer, "<%s%s[%d]: -> %s%s\n", ANSI_COLOR_GREEN, b->file_path, i, b->contents[i], ANSI_COLOR_RESET);
      strcat(message, buffer);
      return false; 
    }
  }
  return true;
}
