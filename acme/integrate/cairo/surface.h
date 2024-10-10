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


inline ::pixmap get_raw_data_from_cairo_surface(::memory & memoryHost, cairo_surface_t *surface) {
   // Ensure the surface format is ARGB32
   if (cairo_image_surface_get_format(surface) != CAIRO_FORMAT_ARGB32) {
      fprintf(stderr, "Surface format is not ARGB32.\n");
      return{};
   }

   // Get the width, height, and stride of the surface
   int width = cairo_image_surface_get_width(surface);
   int height = cairo_image_surface_get_height(surface);
   int stride = cairo_image_surface_get_stride(surface);

   // Get the raw pixel data
   unsigned char *data = cairo_image_surface_get_data(surface);

   // Ensure the data is not NULL
   if (!data) {
      fprintf(stderr, "Failed to get the surface data.\n");
      return{};
   }

   memoryHost.set_size(stride * height);

   ::pixmap pixmap;

   //memcpy(memoryHost.data(), data, memoryHost.size());

   pixmap.m_pimage32 = (::image32_t *) memoryHost.data();
   pixmap.m_sizeRaw.cx() = width;
   pixmap.m_sizeRaw.cy() = height;
   pixmap.m_size.cx() = width;
   pixmap.m_size.cy() = height;
   pixmap.m_iScan = stride;

   pixmap.m_pimage32->copy_swap_red_blue(width, height,stride, (image32_t*) data, stride);

   return pixmap;

}
