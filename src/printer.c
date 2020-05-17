#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/paragraph.h"
#include "../includes/printer.h"
#include "../includes/file_t.h"

char* format_left_justified(paragraph* p){
  char buffer[BUFSIZ];
  char* left_justified = (char*)malloc(MAX_FORMAT_STR_SIZ * sizeof(char));

  memset(buffer, 0, sizeof(buffer));
  memset(left_justified, 0, strlen(left_justified));

  for(int i = p->begin; i < p->end; ++i){
    sprintf(buffer, "%-49s%s", "<", p->master_content[i]);
    strcat(left_justified, buffer);
    memset(buffer, 0, sizeof(buffer));
  }
  return left_justified;
}

char* format_right_justified(paragraph* p){
  char buffer[BUFSIZ];
  char* right_justified = (char*)malloc(MAX_FORMAT_STR_SIZ * sizeof(char));

  memset(buffer, 0, sizeof(buffer));
  memset(right_justified, 0, strlen(right_justified));

  for(int i = p->begin; i < p->end; ++i){
    sprintf(buffer, "%50s %s", ">", p->master_content[i]);
    strcat(right_justified, buffer);
    memset(buffer, 0, sizeof(buffer));
  }
  return right_justified;
}

void print_left_justified(paragraph* p){
  if(p == NULL){ return; }
  char* left = format_left_justified(p);
  printf("%s\n", left);
  free(left);
  left = NULL;
}



void print_right_justified(paragraph* p){
  if(p == NULL){ return; }
  char* right = format_right_justified(p);
  printf("%s\n", right);
  free(right);
  right = NULL;
}


void format_both_on_line(paragraph* p, paragraph* q){
  if(p == NULL || q == NULL){  return; }

  char* p_format = format_left_justified(p);
  char* q_format = format_right_justified(q);
  printf("%s %s", p_format, q_format);
  free(p_format);
  free(q_format);
  p_format = q_format = NULL;
}


void print_both(paragraph* p, bool toggle){
  char buffer[BUFSIZ];
  for(int i = p->begin; i < p->end; ++i){
    char* content = p->master_content[i];
    size_t len = strlen(content);
    if(len > 0){ strncpy(buffer, content, len); }
    buffer[len-1] = '\0';
    if(toggle){
      printf("%-50s %s", buffer, content);
    } else{
      printf("%s", content);
    }
    memset(buffer, 0, sizeof(buffer));
  }
}

