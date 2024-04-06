//
// Created by camilo on 31/01/2022 20:15 <3ThomasBorregaardSorensen!! Thomas Likes number 5!!
//
#pragma once


#include "acme/user/nano/device.h"


#include <CoreGraphics/CoreGraphics.h>


namespace quartz2d
{

   class CLASS_DECL_ACME nano_device :
      virtual public ::nano_device
   {
   public:


      CGContextRef                  m_pdc;
      bool                          m_bOwn;

      
      nano_device();
      nano_device(CGContextRef pdc);
      ~nano_device() override;


      void _draw_text(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano_brush * pnanobrushBack, ::nano_brush * pnanobrushText, ::nano_font * pnanofont) override;
      
      ::size_i32 get_text_extents(const ::string & str, ::nano_font * pnanofont) override;

      void rectangle(const ::rectangle_i32 & rectangle, ::nano_brush * pnanobrush, ::nano_pen * pnanopen) override;


      void _set_source(const ::color::color & color);


      void _set_fill_color(const ::color::color & color);
      
      
      void _select_font(::nano_font * pnanofont);
      
      
   };


} // namespace quartz2d



