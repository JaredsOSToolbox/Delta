#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "includes/file_struct.h"

typedef struct file_ file_t;

int main(){
  file_t * a = file_constructor("inputs/test");
  for(int i = 0; i < a->length; ++i){
    char* mutate = strdup(a->contents[i]);
    char* token = strtok(mutate, " ");
    while(token){
      printf("%s\n", token);
      token = strtok(NULL, " ");
    }
    free(mutate);
  }
  file_destructor(a);
  return 0;
}
