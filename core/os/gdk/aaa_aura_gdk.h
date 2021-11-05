#pragma once


#include <gdk/gdk.h>


void copy(RECT32 * prectTarget, const GdkRectangle * prectSource);
void copy(GdkRectangle * prectTarget, const RECT32 * prectSource);

