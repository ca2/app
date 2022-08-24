#pragma once


namespace draw2d
{


   class object;
   

   class cursor;
   class brush;
   class pen;
   class region;
   class path;
   class graphics;
   class bitmap;


   class graphics_call_base;


   using graphics_call_array = __pointer_array(graphics_call_base);


} // namespace draw2d


CLASS_DECL_AURA void vertical_swap_copy_colorref_swap_red_blue(::color32_t * pcolorrefDst, int cxParam, int cyParam, int iStrideDst, const ::color32_t * pcolorrefSrc, int iStrideSrc);




