#pragma once


class color_array;
class image32_array;


namespace draw2d
{


   class object;
   class draw2d;


   class printer;
   

   class cursor;
   class brush;
   class pen;
   class region;
   class path;
   class host;
   class graphics;
   class bitmap;
   class icon;
   class bitmap;


   class item;


   class fastblur;


   class path_optimization;


   class graphics_extension;


   class graphics_call_base;


   using graphics_call_array = pointer_array < graphics_call_base >;

   using icon_pointer = ::pointer<icon>;
   using brush_pointer = ::pointer<brush>;
   using pen_pointer = ::pointer<pen>;
   using bitmap_pointer = ::pointer<bitmap>;
   using path_pointer = ::pointer<path>;
   using region_pointer = ::pointer<region>;


   class icon;


   class matrix;


   CLASS_DECL_ACME void colora_from_quada(color_array & colora, WINRGBQUAD * prgbquad, int iCount);


} // namespace draw2d


CLASS_DECL_AURA void vertical_swap_copy_image32_swap_red_blue(::color32_t * pimage32Dst, int cxParam, int cyParam, int iStrideDst, const ::color32_t * pimage32Src, int iStrideSrc);




