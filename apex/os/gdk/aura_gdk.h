#pragma once


#include <gdk/gdk.h>


void copy(RECT * prectTarget, const GdkRectangle * prectSource);
void copy(GdkRectangle * prectTarget, const RECT * prectSource);

