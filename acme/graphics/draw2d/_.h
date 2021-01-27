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


#ifdef WINDOWS


typedef RGBQUAD WINRGBQUAD;
#ifdef _UWP
typedef WINRGBQUAD * LPWINRGBQUAD;
#else
typedef LPRGBQUAD LPWINRGBQUAD;
#endif


#else


typedef struct tagWINRGBQUAD {
   byte    rgbBlue;
   byte    rgbGreen;
   byte    rgbRed;
   byte    rgbReserved;
} WINRGBQUAD, * LPWINRGBQUAD;


#endif


#include "_const.h"


#include "colorref_array.h"


#include "opacity.h"


#include "color.h"




CLASS_DECL_ACME string os_font_name(enum_font efont);
CLASS_DECL_ACME string os_font_name(enum_operating_system eoperatingsystem, int iVariant, enum_font efont);
CLASS_DECL_ACME string linux_font_name(enum_linux_distribution elinuxdistribution, enum_font efont);