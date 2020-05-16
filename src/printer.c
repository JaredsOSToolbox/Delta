#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/paragraph.h"
#include "../includes/printer.h"
#include "../includes/file_t.h"

void print_left_mod(char* left){
  char buffer[BUFSIZ];
  sprintf(buffer, "%-49s%s", left, "<");
  printf("%s", buffer);
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


// these implementations work for me, sorta

char* strip(char* input, char find, char replace){
  char* pos;
  if((pos = strchr(input, find)) != NULL){ *pos = replace; } 
  return input;
}

/*void print_left(char* left) {*/
  /*char buf[BUFSIZ];*/
  
  /*strcpy(buf, left);*/
  /*int j = 0, len = (int)strlen(buf) - 1;*/
  /*for (j = 0; j <= 48 - len ; ++j) { buf[len + j] = ' '; }*/
  /*buf[len + j++] = '<';*/
  /*buf[len + j++] = '\0';*/
  /*printf("%s\n", buf);*/
/*}*/

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

void paragraph_print(paragraph* p, file_t* a, void (*fp)(char*)) {
  if (p == NULL) { return; }
  for (int i = p->begin; i <= p->end && i != a->length; ++i) { fp(p->master_content[i]); }
}

void print_revamped(file_t* a, file_t* b){
  if(a == NULL || b == NULL){ return; }
  paragraph* p = para_first(a);
  paragraph* q = para_first(b);
  if(p == NULL || q == NULL){ return; }

  bool found = false;

  paragraph* qlast = q;
  while (p != NULL) {
    qlast = q;
    found = false;
    /*while (q != NULL && (found = para_equal(a, p, b, q)) == false) {*/
    while (q != NULL && (found = para_equal(*a, p, *b, q)) == false) {
      printf("in the first q loop!\n");
      q = para_next(b, q);
    }
    q = qlast;

    if (found) {
      /*while ((found = para_equal(a, p, b, q)) == false) {*/
      while ((found = para_equal(*a, p, *b, q)) == false) {
        printf("print right!\n");
        paragraph_print(p, a, print_right);
        q = para_next(b, q);
        qlast = q;
      }
      printf("print both!\n");
      paragraph_print(q, b, print_both);
      p = para_next(a, p);
      q = para_next(b, q);
    } else {
      paragraph_print(p, a, print_left_mod);
      p = para_next(a, p);
    }
  }
  while (q != NULL) {
    printf("print right outer!\n");
    paragraph_print(q, b, print_right);
    q = para_next(b, q);
  }
}
