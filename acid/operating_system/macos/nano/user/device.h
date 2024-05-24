//
// Created by camilo on 31/01/2022 20:15 <3ThomasBorregaardSorensen!! Thomas Likes number 5!!
//
#pragma once


#include "acid/nano/user/device.h"


#include <CoreGraphics/CoreGraphics.h>


namespace quartz2d
{

   namespace nano
   {

  
      namespace user
      {


   class CLASS_DECL_ACID device :
      virtual public ::nano::user::device
   {
   public:


      CGContextRef                  m_pdc;
      bool                          m_bOwn;

      
      device();
      device(CGContextRef pdc);
      ~device() override;


      void _draw_text(const ::string & str, const ::rectangle_i32 & rectangleText, const ::e_align & ealign, const ::e_draw_text & edrawtext, ::nano::user::brush * pnanobrushBack, ::nano::user::brush * pnanobrushText, ::nano::user::font * pnanofont) override;
      
      ::size_i32 get_text_extents(const ::string & str, ::nano::user::font * pnanofont) override;

      void rectangle(const ::rectangle_i32 & rectangle, ::nano::user::brush * pnanobrush, ::nano::user::pen * pnanopen) override;


      void _set_source(const ::color::color & color);


      void _set_fill_color(const ::color::color & color);
      
      
      void _select_font(::nano::user::font * pnanofont);
      
      
   };



      } //namespace user


   } //namespace nano


} // namespace quartz2d





