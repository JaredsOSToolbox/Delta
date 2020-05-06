#include <stdio.h>
#include <string.h>
#include "../includes/printer.h"
#include "../includes/paragraph.h"

#define MAX_FORMAT_STR_SIZ 1000

void print_left(char* left) {
  char buf[BUFSIZ];
  
  strcpy(buf, left);
  int j = 0, len = (int)strlen(buf) - 1;
  for (j = 0; j <= 48 - len ; ++j) { buf[len + j] = ' '; }
  buf[len + j++] = '<';
  buf[len + j++] = '\0';
  printf("%s\n", buf);
}

void print_right(char* right) {
  if (right == NULL) { return; }
  printf("%50s %s", ">", right);
}

void print_both(char* left_right) {
  char buf[BUFSIZ];
  size_t len = strlen(left_right);
  if (len > 0) { strncpy(buf, left_right, len); }
  buf[len - 1] = '\0';
  printf("%-50s %s", buf, left_right);
}


// these implementations work for me

char* format_left_justified(paragraph* p){
  printf("calling %s\n", __func__);
  size_t EOS;
  char buffer[BUFSIZ];
  char* left_justified = (char*)malloc(MAX_FORMAT_STR_SIZ * sizeof(char));
  for(int i = p->begin; i < p->end; ++i){
    sprintf(buffer, "%s %s", "<", p->master_content[i]);
    strcat(left_justified, buffer);
    EOS+=strlen(buffer);
  }
  left_justified[EOS-1] = '\0';
  return left_justified;
}
void print_left_justified(paragraph* p){
  if(p == NULL){ return; }
  char* left = format_left_justified(p);
  printf("%s", left);
  printf("\n");
  free(left);
  left = NULL;
}

void print_right_justified(paragraph* p){
  if(p == NULL){ return; }
  for(int i = p->begin; i < p->end; ++i){
    printf("%50s %s", ">", p->master_content[i]);
  }
  printf("\n");
}

