#pragma once


CLASS_DECL_ACME COLORREF make_colorref(i32 a, i32 rect, i32 g, i32 b);


inline byte clampAndConvert(double v)
{


   if (v < 0)
      return 0;
   if (v > 255)
      return 255;
   return (byte)(v);


}

CLASS_DECL_ACME COLORREF argb_swap_rb(COLORREF cr);


#include "_const.h"


#include "colorref_array.h"


#include "color.h"
