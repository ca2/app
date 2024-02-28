//
// Created by camilo on 2021-08-17 <3ThomasBS_.
//

/*
 * Librsvg rasterization wrapper
 * Copyright (c) 2017 Rostislav Pehlivanov <atomnuker@gmail.com>
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "framework.h"
#include "cairo/cairo-features.h"
#include <cairo/cairo.h>
//#include <librsvg/rsvg.h>


namespace imaging_freeimage
{


//   void context_image::load_svg(::image * pimage, memory & memory)
//   {
//
//      return ::context_image::load_svg(pimage, memory);
//
////      int ret;
////
////      RsvgDimensionData unscaled_dimensions, dimensions;
////      cairo_surface_t *image;
////      cairo_t *crender = NULL;
////      GError *error = NULL;
////
////      auto pszData = (const char *) memory.get_data();
////
////      auto size = memory.get_size();
////
////
////      auto handle = rsvg_handle_new_from_data(pszData, size, &error);
////      if (error) {
////         g_error_free(error);
////         return error_invalid_buffer;
////      }
////
////      rsvg_handle_get_dimensions(handle, &dimensions);
////      rsvg_handle_get_dimensions(handle, &unscaled_dimensions);
////      dimensions.width  = pimage->width()  ? pimage->width()  : dimensions.width;
////      dimensions.height = pimage->height() ? pimage->height() : dimensions.height;
//////      if (s->keep_ar && (s->width || s->height)) {
//////         double default_ar = unscaled_dimensions.width/(double)unscaled_dimensions.height;
//////         if (!s->width)
//////            dimensions.width  = lrintf(dimensions.height * default_ar);
//////         else
//////            dimensions.height = lrintf(dimensions.width  / default_ar);
//////      }
////
////      if(!pimage->create({dimensions.width, dimensions.height}))
////      {
////         return error_failed;
////
////      }
////
////
////      image = cairo_image_surface_create_for_data(
////         (unsigned char *) pimage->get_data(), CAIRO_FORMAT_ARGB32,
////                                                  pimage->width(), pimage->height(),
////                                                  pimage->scan_size());
////      if (cairo_surface_status(image) != CAIRO_STATUS_SUCCESS)
////         return error_invalid_buffer;
////
////      crender = cairo_create(image);
////
////      cairo_save(crender);
////      cairo_set_operator(crender, CAIRO_OPERATOR_CLEAR);
////      cairo_paint(crender);
////      cairo_restore(crender);
////
////      cairo_scale(crender, dimensions.width / (double)unscaled_dimensions.width,
////                  dimensions.height / (double)unscaled_dimensions.height);
////
////      rsvg_handle_render_cairo(handle, crender);
////
////      cairo_destroy(crender);
////      cairo_surface_destroy(image);
////      g_object_unref(handle);
////
////      return success;
//
//   }


} // namespace imaging_freeimage
