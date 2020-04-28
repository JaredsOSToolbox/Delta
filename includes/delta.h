#pragma once
#include <stdbool.h>


bool version, brief, report_identical, normal, side_by_side, left_column, suppress_common, context, unified;

void set_flags(const char*, const char*, const char*, bool*);
