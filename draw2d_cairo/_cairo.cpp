// Created by camilo on 2021-01-16 11:49 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif


void destroy_pointer(cairo_surface_t* p)
{

   cairo_surface_destroy(p);

}


void destroy_pointer(cairo_pattern_t* p)
{

   cairo_pattern_destroy(p);

}

