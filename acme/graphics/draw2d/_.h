#pragma once


CLASS_DECL_ACME color32_t make_colorref(i32 a, i32 rect, i32 g, i32 b);


inline byte clampAndConvert(double v)
{


   if (v < 0)
      return 0;
   if (v > 255)
      return 255;
   return (byte)(v);


}

CLASS_DECL_ACME color32_t argb_swap_rb(color32_t cr);


#include "_const.h"


#include "colorref_array.h"


#include "color.h"
