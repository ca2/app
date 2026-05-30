#pragma once


class color_array;
class image32_array;


enum enum_graphics
{

   e_graphics_none = 0,
   e_graphics_from_context = 1,
   e_graphics_layout = 2,
   e_graphics_draw = 4,

};

DECLARE_C_FLAG(e_graphics, enum_graphics);

namespace draw2d
{


   class object;
   class draw2d;


   class printer;
   

   class brush;
   class pen;
   class region;
   class path;
   class host;
   class graphics;
   class bitmap;


   class graphics_context;


   class item;


   class path_optimization;


   class graphics_extension;


   class graphics_call_base;


   class offset_context;


   using graphics_call_array = pointer_array < graphics_call_base >;

   using brush_pointer = ::pointer<brush>;
   using pen_pointer = ::pointer<pen>;
   using bitmap_pointer = ::pointer<bitmap>;
   using path_pointer = ::pointer<path>;
   using region_pointer = ::pointer<region>;


   CLASS_DECL_ACME void colora_from_quada(color_array & colora, WINRGBQUAD * prgbquad, ::i32 iCount);


} // namespace draw2d


CLASS_DECL_AURA void vertical_swap_copy_image32_swap_red_blue(::color32_t * pimage32Dst, ::i32 cxParam, ::i32 cyParam, ::i32 iStrideDst, const ::color32_t * pimage32Src, ::i32 iStrideSrc);




