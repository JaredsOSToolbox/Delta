#pragma once

#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define MAX_FORMAT_STR_SIZ 1000

void print_left(char*);
void print_right(char*);
void print_both(char*);
char* strip_pattern(char*);
