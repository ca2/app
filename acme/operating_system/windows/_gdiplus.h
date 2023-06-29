// Created by camilo on 2023-06-28 19:20 <3ThomasBorregaardSorensen!!
#pragma once


#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#include <gdiplus.h>
#include "acme/graphics/write_text/font_size.h"


constexpr Gdiplus::REAL gdiplus_font_size(const write_text::font_size & fontsize)
{

   return (Gdiplus::REAL) (::f64) fontsize;

}

constexpr Gdiplus::Unit gdiplus_font_unit(const write_text::font_size & fontsize)
{

   switch (fontsize.m_eunit)
   {
   case e_unit_pixel:
      return Gdiplus::UnitPixel;
   case e_unit_point:
      return Gdiplus::UnitPoint;
   default:
      throw fontsize.m_eunit;
   }

}
