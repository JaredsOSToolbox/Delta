#pragma once
#include <stdbool.h>


#define ARGC_ERROR 1
#define TOOMANYFILES_ERROR 2
#define CONFLICTING_OUTPUT_OPTIONS 3

#define MAXSTRINGS 1024
#define MAXPARAS 4096

#define HASHLEN 200


const char* AUTHOR = "Jared Dyreson";
const char* COAUTHOR = "William McCarthy";
const char* INSTITUTION = "California State University Fullerton";
bool version, brief, report_identical, normal, side_by_side, left_column, suppress_common, context, unified;

void set_flags(const char*, const char*, const char*, bool*);
