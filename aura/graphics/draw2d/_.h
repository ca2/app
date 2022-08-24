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
   class icon;


   class graphics_call_base;


   using graphics_call_array = __pointer_array(graphics_call_base);

   using icon_pointer = __pointer(::draw2d::icon);

} // namespace draw2d


CLASS_DECL_AURA void vertical_swap_copy_colorref_swap_red_blue(::color32_t * pcolorrefDst, int cxParam, int cyParam, int iStrideDst, const ::color32_t * pcolorrefSrc, int iStrideSrc);




