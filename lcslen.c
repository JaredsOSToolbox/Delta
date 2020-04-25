#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "includes/file_struct.h"
#include "includes/lcslen.h"

matrix* matrix_constructor(struct file_* a, struct file_* b){
  matrix* m = (matrix *)malloc(sizeof(matrix));
  m->entry_one = a->contents;
  m->entry_two = b->contents;
  m->x = a->length;
  m->y = b->length;
  m->grid = generate_grid(m);
  m->lcs_value = (char*)malloc((m->x+m->y)*sizeof(char));
  return m;
}

void matrix_destructor(matrix* m){
  for(int i = 0; i < m->x; ++i){ free(m->grid[i]); }
  free(m->grid);
  free(m);
}


void print_matrix(matrix* m){
 for(int i = 0; i < m->x; ++i){
   for(int j = 0; j < m->y; ++j){
     printf("%d ", m->grid[i][j]);
   }
   printf("\n");
 }
}

void matrix_repr(matrix* m){
  printf("Dimensions: %d x %d\n", m->x, m->y);
  printf("Grid: \n");
  print_matrix(m);
}

int** generate_grid(matrix* m){
  int **a = (int **)malloc(sizeof(int *)*m->x);
  for(int i = 0; i < m->x; i++){ 
    a[i] = (int *)malloc(sizeof(int)*m->y); 
    for(int j = 0; j < m->y; ++j){ a[i][j] = 0; }
  }
  return a;
}

int my_max(int x, int y){ return (x > y) ? x : y; }
bool is_square(matrix* m){ return (m->x == m->y) ? true : false; }

void lcslen(matrix* m){
  char *xi, *yi;
  for(int i = 0; i < m->x; ++i){
    xi = m->entry_one[i];
    for(int j = 0; j < m->y; ++j){
      yi = m->entry_two[j];
      int x_index = (i-1 < 0) ? 0 : i-1;
      int y_index = (j-1 < 0) ? 0 : j-1;
      if(strcmp(xi, yi) == 0){ 
        m->grid[i][j] = 1 + m->grid[x_index][y_index]; 
      } else{
        m->grid[i][j] = my_max(m->grid[i][y_index], m->grid[x_index][j]);
      }
    }
  }
}

char* reverse_string(char* str){
  size_t len = strlen(str)-1;
  char* n = (char *)malloc(len * sizeof(char));
  for(size_t i = len; i <= len; --i){
    strncat(n, &str[i], 1);
  }
  n[len+1] = '\0';
  return n;
}

int string_sum(char* s){
  int sum = 0;
  while(*s++ != '\0'){ sum+=(int)*s; }
  return sum;

}

int backtrack(int** grid, char** x, char** y, int i, int j, char* lcs_val){
  int x_index = (i-1 < 0) ? 0 : i-1;
  int y_index = (j-1 < 0) ? 0 : j-1;
  if((i-1 < 0) || (j-1 < 0)){ return 0; }
  else if(strcmp(x[i], y[j]) ==0){
    strncat(lcs_val, x[i], 1);
    return backtrack(grid, x, y, x_index, y_index, lcs_val)+string_sum(x[i]);
  }
  else if(grid[i][y_index] >= grid[x_index][j]){ return backtrack(grid, x, y, i, y_index, lcs_val); }
  else if(grid[i][y_index] < grid[x_index][j]){ return backtrack(grid, x, y, x_index, j, lcs_val); }
}

int lcs(matrix* m){
  lcslen(m);
  return backtrack(m->grid, m->entry_one, m->entry_two, m->x, m->y, m->lcs_value);
  /*free(m->lcs_value);*/
  /*m->lcs_value = reversed;*/
  /*return lcs_int_repr;*/
}

void print_match(char* message, bool newline){ 
  printf(ANSI_COLOR_GREEN "+ %s%s" ANSI_COLOR_RESET, message, (newline) ? "\n" : ""); 
}

void print_nonmatch(char* message, bool newline){ 
  printf(ANSI_COLOR_RED "- %s%s" ANSI_COLOR_RESET, message, (newline) ? "\n" : ""); 
}

void print_diff(int** grid, char** x, char** y, int i, int j){
  int i_ = (i-1 < 0) ? 0 : i-1;
  int j_ = (j-1 < 0) ? 0 : j-1;

  printf("callng print_diff(grid, %s, %s, %d, %d)\n", x[i], y[i], i, j);

  if(i < 0 && j < 0){ return; }
  else if(i < 0){
    print_diff(grid, x, y, i, j-1);
    printf("+ %s", y[i]);
    /*print_match(y[i], false);*/
  }
  else if(j < 0){
    print_diff(grid, x, y, i-1, j);
    printf("- %s", x[i]);
    /*print_nonmatch(x[i], false);*/
  }
  /*else if(x[i] == y[i]){*/
  else if(strcmp(x[i], y[i]) == 0){
     /*this is a match, can be ignored in optional flags*/
     /*flag: print_matches == true*/
    print_diff(grid, x, y, i-1, j-1);
    printf("   %s", x[i]);
  }
  else if(grid[i][j-1] >= grid[i-1][j]){
    print_diff(grid, x, y, i, j-1);
    printf("+  %s", y[j]);
    /*print_match(y[i], false);*/
  }
  /*else if(grid[i][j_] < grid[i_][j]){*/
    /*print_diff(grid, x, y, i_, j);*/
    /*printf("- %s", x[i]);*/
    /*print_nonmatch(x[i], false);*/
  /*}*/
}

void diff(matrix* m){
  lcs(m);
  print_diff(m->grid, m->entry_one, m->entry_two, m->x-1, m->y-1);
}

int main(int argc, char* argv[]){
  struct file_* f_a = file_constructor("inputs/left.txt");
  struct file_* f_b = file_constructor("inputs/right.txt");
  matrix* m = matrix_constructor(f_a, f_b);
  diff(m);
  matrix_destructor(m);
  return 0;
}
