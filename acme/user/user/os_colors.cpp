#include "framework.h"
#include "acme/constant/id.h"


::color32_t argb_swap_rb(::color32_t color32)
{

   return argb(
      colorref_get_a_value(color32),
      colorref_get_b_value(color32),
      colorref_get_g_value(color32),
      colorref_get_r_value(color32));

}


