// Created by camilo on 2021-01-16 11:49 BRT <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "aura/graphics/draw2d/matrix.h"


void destroy_pointer(cairo_surface_t* p)
{

   cairo_surface_destroy(p);

}


void destroy_pointer(cairo_pattern_t* p)
{

   cairo_pattern_destroy(p);

}




CLASS_DECL_DRAW2D_CAIRO void copy(::draw2d::matrix * pmatrix, const cairo_matrix_t * pcairomatrix)
{

   pmatrix->a1 = pcairomatrix->xx;
   pmatrix->a2 = pcairomatrix->yx;
   pmatrix->b1 = pcairomatrix->xy;
   pmatrix->b2 = pcairomatrix->yy;
   pmatrix->c1 = pcairomatrix->x0;
   pmatrix->c2 = pcairomatrix->y0;

}


CLASS_DECL_DRAW2D_CAIRO void copy(cairo_matrix_t * pcairomatrix, const ::draw2d::matrix * pmatrix)
{

   pcairomatrix->xx = pmatrix->a1;
   pcairomatrix->yx = pmatrix->a2;
   pcairomatrix->xy = pmatrix->b1;
   pcairomatrix->yy = pmatrix->b2;
   pcairomatrix->x0 = pmatrix->c1;
   pcairomatrix->y0 = pmatrix->c2;

}



