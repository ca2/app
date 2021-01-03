#pragma once


#include "debug.h"


off_t tell64(int fd);


::e_status os_defer_init_gtk();


#include "gdk.h"


typedef struct _cairo_rectangle_int cairo_rectangle_int_t;
typedef cairo_rectangle_int_t         GdkRectangle;


void copy(RECT32 * prectTarget, const GdkRectangle * prectSource);
void copy(GdkRectangle * prectTarget, const RECT32 * prectSource);



