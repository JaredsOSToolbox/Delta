#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../includes/paragraph.h"
#include "../includes/file_struct.h"

#define NUMBER_OF_PARAGRAPHS 100

paragraph* paragraph_constructor(char** content, int begin, int end){
  paragraph* para = (paragraph*)malloc(sizeof(paragraph));
  para->master_content = content;
  para->begin = begin;
  para->end = end;
  para->size = (end-begin)+1;
  return para;
}

paragraph_network* paragraph_network_constructor(){
  paragraph_network* network = (paragraph_network*)malloc(sizeof(paragraph_constructor));
  network->size = 0;
  network->stack_pointer = 0;
  network->paragraph_nodes = (paragraph*)malloc(NUMBER_OF_PARAGRAPHS * sizeof(paragraph));
  return network;
}

void paragraph_destructor(paragraph* para){
  free(para);
}

void paragraph_network_destructor(paragraph_network* network){
  for(int i = 0; i < network->size; ++i){
    paragraph_destructor(network->paragraph_nodes[i]);
  }
}

void paragraph_network_add_paragraph(paragraph_network* network, paragraph* para){
  if(network->size > NUMBER_OF_PARAGRAPHS){
    fprintf(stderr, "cannot insert into network, too many nodes\n");
    return;
  }
  network->paragraph_nodes[network->size++] = para;
}

void paragraph_print(FILE* output,  paragraph* para){
  for(int i = para->begin; i < para->end; ++i){
    fprintf(output, "%s", para->master_content[i]);
  }
  fprintf(output, "\n");
}

bool para_equal(paragraph* p, paragraph* q) {
  if (p == NULL || q == NULL) { return false; }
  else if(p->size != q->size){ return false; }
  int i = p->begin, j = q->begin, equal = 0;
  while ((equal = strcmp(p->master_content[i], q->master_content[i])) == 0 && i < p->end && j < q->end) { ++i; ++j; }
  return true;
}

paragraph* para_next(struct file_* a, paragraph* p) {
  if (p == NULL || p->end == a->length) { return NULL; }
  
  int i;
  paragraph* pnew = paragraph_constructor(p->master_content, p->end + 1, p->end + 1);
  for (i = pnew->begin; i < a->length && strcmp(p->master_content[i], "\n") != 0; ++i) { }
  pnew->end = i;
  
  if (pnew->begin >= a->length) {
    free(pnew);
    pnew = NULL;
  }
  return pnew;
}

paragraph* para_first(struct file_* a) {
  paragraph* p = paragraph_constructor(a->contents, 0, -1);
  return para_next(a, p);
}

void slice(struct file_* a){
  paragraph* current = para_first(a);
  while(current != NULL){
    paragraph_network_add_paragraph(a->para_network, current);
    current = para_next(a, current);
  }
}
