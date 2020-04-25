#include <stdio.h>

#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"

int main(int argc, const char* argv[]){
  const char* message = "Hello World";
  const char* other_message = "Goodbye World";
  printf(ANSI_COLOR_RED "< %s\n" ANSI_COLOR_RESET, message);
  printf(ANSI_COLOR_GREEN "> %s\n" ANSI_COLOR_RESET, other_message);
  return 0;
}
