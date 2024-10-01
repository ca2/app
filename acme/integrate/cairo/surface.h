//
// Created by camilo on 2024-10-01 05:36 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/graphics/image/pixmap.h"
#include <cairo/cairo.h>


inline cairo_surface_t * cairo_surface_for_pixmap(::pixmap & pixmap)
{

   return cairo_image_surface_create_for_data(
      (unsigned char *) pixmap.m_pimage32,              // Pointer to the raw data in memory
      CAIRO_FORMAT_ARGB32,    // Data format (ARGB32)
      pixmap.width(),                  // Width of the surface
      pixmap.height(),                 // Height of the surface
      pixmap.m_iScan                 // Stride (number of bytes per row)
   );

}
