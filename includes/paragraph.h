#pragma once
typedef struct paragraph{
  int begin, end;
  char** master_content;
  size_t size;
  //char* name;
} paragraph;

typedef struct paragraph_network{
  paragraph** paragraph_nodes;
  size_t size;
  size_t stack_pointer;
  size_t master_size;
  //char* name;
} paragraph_network;


paragraph* paragraph_constructor(char**, int, int);
paragraph_network* paragraph_network_constructor(void);

void paragraph_destructor(paragraph*);
void paragraph_network_destructor(paragraph_network*);

void paragraph_network_add_paragraph(paragraph_network*, paragraph*);
