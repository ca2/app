#include "framework.h"
#include "acme/constant/id.h"
#include "acme/graphics/draw2d/image32.h"


::color32_t argb_swap_red_blue(::color32_t color32)
{

   return argb(color32.u8_opacity(), color32.u8_blue(), color32.u8_green(), color32.u8_red());

}



