#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"

typedef struct matrix matrix;

struct matrix{
  char** entry_one;
  char** entry_two;
  char* lcs_value;
  int x, y;
  int** grid;
};

// constructor and destructor
matrix* matrix_constructor(struct file_*, struct file_*);
void matrix_destructor(matrix*);

// member functions

int my_max(int, int);
int** generate_grid(matrix*);
void print_matrix(matrix*);
bool is_square(matrix*);
void matrix_repr(matrix*);
