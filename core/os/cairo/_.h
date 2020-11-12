#pragma once


#include <cairo/cairo.h>


void copy(RECT32 * prectTarget, const cairo_rectangle_int_t * prectSource);
void copy(cairo_rectangle_int_t * prectTarget, const RECT32 * prectSource);

