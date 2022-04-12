//
// Created by camilo on 31/01/2022 20:15 <3ThomasBorregaardSørensen!! Thomas Likes number 5!!
//
#pragma once


#include <cairo/cairo-features.h>
#include <cairo/cairo.h>
#include <cairo/cairo-ft.h>
#include <cairo/cairo-xlib.h>

namespace xcb
{

   class CLASS_DECL_ACME nano_device :
      virtual public ::nano_device
   {
   public:


      cairo_surface_t *    m_psurfaceMemory;
      cairo_t *            m_pdc;


      nano_device();
      nano_device(cairo_t * pdc);
      ~nano_device() override;


      void _draw_text(const ::string & strMessage, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano_brush * pnanobrushBack, ::nano_brush * pnanobrushText, ::nano_font * pnanofont) override;
      ::size_i32 get_text_extents(const ::string & str, ::nano_font * pnanofont) override;
      void rectangle(const ::rectangle_i32 & rectangle, ::nano_brush * pnanobrush, ::nano_pen * pnanopen) override;


      //XColor _alloc_xcolor(const ::color::color & color);
      //void _set_foreground(const ::color::color & color);
      //void _set_background(const ::color::color & color);

      void _set_source(const ::color::color & color);


      //void set_antialias(bool bAntialiasOn);


   };


} // namespace xcb



