#include <stdio.h>
#include <string.h>
#include "../includes/printer.h"

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
