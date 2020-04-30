#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../includes/paragraph.h"

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
    fprintf(output, "%s\n", para->master_content[i]);
  }
}
