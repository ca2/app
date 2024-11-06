#include "framework.h"
#include "acme/constant/id.h"
#include "acme/graphics/image/image32.h"


::color32_t argb_swap_red_blue(::color32_t color32)
{

   return argb(color32.byte_opacity(), color32.byte_blue(), color32.byte_green(), color32.byte_red());

}



