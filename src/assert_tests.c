#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "../includes/assert_tests.h"
#include "../includes/file_t.h"
#include "../includes/paragraph.h"


void paragraph_equal_assert(){
  file_t* file_a = file_constructor("inputs/test");
  file_t* file_b = file_constructor("inputs/test");

  paragraph** a_paras = file_a->para_network->paragraph_nodes;
  paragraph** b_paras = file_b->para_network->paragraph_nodes;

  // each increment moves to a new paragraph

  /*paragraph_vanilla_print(*a_paras);*/
  /*paragraph_vanilla_print(*b_paras);*/
  assert(paragraph_equal(*a_paras++, *b_paras++) == true);

  /*paragraph_vanilla_print(*a_paras);*/
  /*paragraph_vanilla_print(*b_paras);*/
  assert(paragraph_equal(*a_paras++, *b_paras++) == true);

  /*paragraph_vanilla_print(*a_paras);*/
  /*paragraph_vanilla_print(*b_paras);*/
  // this tracked down a bug where paragraphs were not being properly compared. This function has been breaking alot for some reason
  assert(paragraph_equal(*a_paras, *b_paras) == true);

  file_destructor(file_a);
  file_destructor(file_b);
}

void paragraph_network_equal_assert(){
  file_t* file_a = file_constructor("inputs/test");
  file_t* file_b = file_constructor("inputs/test");

  paragraph_network** a_net = &file_a->para_network;
  paragraph_network** b_net = &file_b->para_network;

  /*print_paragraph_networks(file_a->para_network, file_b->para_network);*/
  assert(paragraph_network_equal(*a_net, *b_net) == true) ;

  file_destructor(file_a);
  file_destructor(file_b);
}

void paragraph_cmp_assert(){
  file_t* file_a = file_constructor("inputs/test");
  file_t* file_b = file_constructor("inputs/test_two");

  paragraph** a_paras = file_a->para_network->paragraph_nodes;
  paragraph** b_paras = file_b->para_network->paragraph_nodes;

  // each increment moves to a new paragraph


  /*while(*a_paras != NULL && *b_paras != NULL){*/
    /*int val = paragraph_cmp(*a_paras++, *b_paras++);*/
    /*printf("value of val: %d\n", val);*/
  /*}*/

  file_destructor(file_a);
  file_destructor(file_b);
}

void all_asserts(){
  /*paragraph_equal_assert();*/
  /*printf("paragraph equal passed!\n");*/
  /*paragraph_network_equal_assert();*/
  /*printf("paragraph network equal passed!\n");*/
  paragraph_cmp_assert(); 
  printf("All assertions passed!\n");
}
