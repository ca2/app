#pragma once


struct color32_t;

struct image32_t;


namespace draw2d
{


   class draw2d;

   class printer;


} // namespace draw2d


inline ::u8 clampAndConvert(double v)
{


   if (v < 0)
      return 0;
   if (v > 255)
      return 255;
   return (::u8)(v);


}








#include "_constant.h"


#include "_system_color.h"


//#include "opacity.h"


//#include "color.h"


//#include "colorref_array.h"





//CLASS_DECL_ACME string os_font_name(enum_font efont);
//CLASS_DECL_ACME string os_font_name(enum_operating_system eoperatingsystem, int iVariant, enum_font efont);
//CLASS_DECL_ACME string linux_font_name(enum_linux_distribution elinuxdistribution, enum_font efont);




//template < class PAYLOAD, typename ARG_VALUE = argument_of < PAYLOAD > >




