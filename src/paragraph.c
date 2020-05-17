#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../includes/file_t.h"
#include "../includes/paragraph.h"
#include "../includes/printer.h"

int my_max(int a, int b){ return (a > b) ? a : b; }

paragraph* paragraph_constructor(char** content, int begin, int end){
  paragraph* para = (paragraph*)malloc(sizeof(paragraph));
  para->master_content = content;
  para->begin = begin;
  para->end = end;
  para->size = (end-begin)+1;
  return para;
}

paragraph_network* paragraph_network_constructor(){
  paragraph_network* network = (paragraph_network*)malloc(sizeof(paragraph));
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

void paragraph_vanilla_print(paragraph* p){
  for(int i = p->begin; i < p->end; ++i){
    printf("%s", p->master_content[i]);
  }
  printf("\n");
}


void paragraph_network_add_paragraph(paragraph_network* network, paragraph* para){
  if(network->size > NUMBER_OF_PARAGRAPHS){
    fprintf(stderr, "cannot insert into network, too many nodes\n");
    return;
  }
  network->paragraph_nodes[network->size++] = para;
}


bool paragraph_equal(paragraph* p, paragraph* q){
  return (paragraph_cmp(p, q) == EQUAL) ? true : false;
}

void print_paragraph_networks(paragraph_network* p, paragraph_network* q){
  bool foundmatch = false;

  paragraph** p_head = p->paragraph_nodes;
  paragraph** q_head = q->paragraph_nodes;

  paragraph* qlast = *q_head;

  while(*p_head != NULL){
    /*qlast = *q_head;*/
    foundmatch = false;
    while(*q_head != NULL && (foundmatch = paragraph_equal(*p_head, *q_head)) == false){*q_head++;}
    /*q_head = &qlast;*/
    if(foundmatch){
      while((foundmatch = paragraph_equal(*p_head, *q_head)) == false){
        print_right_justified(*q_head++);
        /*qlast = *q_head;*/
      }
      format_both_on_line(*p_head++, *q_head++);
    }
    else{
      print_left_justified(*p_head++);
    }
  }
  while(*q_head != NULL){
    print_right_justified(*q_head++);
  }

  while(*p_head !=NULL){
    print_left_justified(*p_head++);
  }
}


bool para_equal(paragraph* p, int p_file_len, paragraph* q, int q_file_len) {
  if (p == NULL || q == NULL) { return false; }
  if (p->size != q->size) { return false; }
  if (p->begin >= p_file_len || q->begin >= q_file_len) { return false; }
  int i = p->begin, j = q->begin, equal = 0;
  while ((equal = strcmp(p->master_content[i], q->master_content[i])) == 0 && i < p->end && j < q->end) { ++i; ++j; }
  return true;
}

bool paragraph_network_equal(paragraph_network* p, paragraph_network* q, int* qlast_index){
  if(p->size != q->size){ return false; }
  for(int i = 0, j = 0; i < p->size && j < q->size; ++i, ++j){
    if(!paragraph_equal(p->paragraph_nodes[i], q->paragraph_nodes[j])){ 
      *qlast_index = j;
      return false; 
    }
  }
  return true;
}

int paragraph_cmp(paragraph* p, paragraph* q){
  if(p == NULL){ return LESS_THAN; }
  else if(q == NULL){ return GREATER_THAN; }

  if(p->size != q->size){
    if(p->size < q->size){ return LESS_THAN; }
    return GREATER_THAN;
  }
  int i = p->begin, j = q->begin;
  int r;

  for(; i < p->end && j < q->end; ++i, ++j){
    r = strcmp(p->master_content[i], q->master_content[j]);
    if(r >= 1){ return LESS_THAN; }
    else if(r <= -1){ return GREATER_THAN; }
  }
  if(i == j){ 
    if(i == p->end && j < q->end){ return LESS_THAN; }
    else if(j == q->end && i < p->end){ return GREATER_THAN; }
    else if(j == q->end && i > p->end){ return GREATER_THAN; }
    else if(i == p->end && j > q->end){ return LESS_THAN; }
    r = strcmp(p->master_content[p->end-1], q->master_content[q->end-1]);
    if(r == EQUAL){ return EQUAL; }
    return (r >= 1) ? GREATER_THAN : LESS_THAN;
  }

  return (i < j) ? LESS_THAN : GREATER_THAN;
}

paragraph* para_next(file_t* a, paragraph* p) {
  if (p == NULL || p->end == a->length) { return NULL; }
  
  int i, j;
  j = i;
  paragraph* pnew = paragraph_constructor(p->master_content, p->end + 1, p->end + 1);
  for (i = pnew->begin; i < a->length && strcmp(p->master_content[i], "\n") != 0; ++i) { }
  pnew->end = i;
  pnew->size = abs(i-j)+1;
  if (pnew->begin >= a->length) {
    free(pnew);
    pnew = NULL;
  }
  return pnew;
}

paragraph* para_first(file_t* a) {
  paragraph* p = paragraph_constructor(a->contents, 0, -1);
  return para_next(a, p);
}

void slice(file_t* a){
  paragraph* current = para_first(a);
  while(current != NULL){
    paragraph_network_add_paragraph(a->para_network, current);
    current = para_next(a, current);
  }
}


