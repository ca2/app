#pragma once


namespace draw2d
{


   class icon;


   CLASS_DECL_AURA void static_initialize();


} // namespace draw2d


namespace draw2d
{


   extern float Cosines[360];
   extern float Sines[360];
   extern i64 CosN[360]; // * 1 << 31
   extern i64 SinN[360];
   extern i64 Cos10N[10]; // until 10 degress
   extern i64 Sin10N[10]; // more precision * 1 << 34
   extern double dPi;


} // namespace draw2d


//#include "fwd.h"
//
//
//#include "common.h"
//#include "matrix.h"
//#include "color_matrix.h"
//
//
//#include "color_filter.h"
//
//
//namespace draw2d
//{
//
//
//   class graphics;
//
//
//} // namespace draw2d
//
//
//#include "object.h"
//#include "pen.h"
//#include "bitmap.h"
//
//
//
//
//CLASS_DECL_AURA void draw_freetype_bitmap(::image * pm_p, i32 Δx, i32 Δy, void * pftbitmap, int x, int y);
//CLASS_DECL_AURA void draw_freetype_bitmap(::image * pm_p, i32 Δx, i32 Δy, void * pftbitmap, int x, int y, byte a, byte rectangle, byte g, byte b);
//
//
//
//#include "brush.h"
//#include "palette.h"
//#include "region.h"
//#include "item.h"
//
//
//#include "aura/graphics/write_text/_.h"
//
//
//#include "path.h"
//
//
//#ifdef WINDOWS
//
//
//namespace direct2d
//{
//
//
//   class plugin;
//
//
//} // namespace draw2d_direct2d
//
//
//#endif
//
//
//#include "aura/graphics/write_text/drawer.h"
//
//
//#include "host.h"
//
//
//#include "aura/platform/draw_context2.h"
//#include "graphics.h"
//
//
//namespace draw2d
//{
//
//
//   class font_list;
//
//
//} // namespace draw2d
//

//#include "aura/windowing/cursor.h"
//#include "aura/windowing/icon.h"



//#include "api.h"
//#include "graphics_extension.h"
//#include "glyph.h"
//#include "glyph_set.h"
////#include "font_enumeration.h"
////#include "fonts.h"
////#include "image_palette.h"
//
//#include "buffered_graphics.h"
//
//#include "task_tool.h"
//
////#include "aura/platform/printer.h"
//
//#include "printer.h"
//
////#include "load_image.h"
////
////#include "context_image.h"
//
//#include "draw2d.h"
//
//
//
////namespace factory
////{
////
////
////   template < >
////   inline __pointer(factory_item_interface) & get_factory_item < ::draw2d::bitmap >()
////   {
////
////      return ::factory::get_factory_item_array()->element_at_grow(e_factory_draw2d_bitmap);
////
////   }
////
////
////   template < >
////   inline __pointer(factory_item_interface) & get_factory_item < ::draw2d::brush >()
////   {
////
////      return ::factory::get_factory_item_array()->element_at_grow(e_factory_draw2d_brush);
////
////   }
////
////
////   template < >
////   inline __pointer(factory_item_interface) & get_factory_item < ::write_text::font >()
////   {
////
////      return ::factory::get_factory_item_array()->element_at_grow(e_factory_draw2d_font);
////
////   }
////
////
////   template < >
////   inline __pointer(factory_item_interface) & get_factory_item < ::draw2d::graphics >()
////   {
////
////      return ::factory::get_factory_item_array()->element_at_grow(e_factory_draw2d_graphics);
////
////   }
////
////
////   template < >
////   inline __pointer(factory_item_interface) & get_factory_item < ::image >()
////   {
////
////      return ::factory::get_factory_item_array()->element_at_grow(e_factory_draw2d_image);
////
////   }
////
////
////   template < >
////   inline __pointer(factory_item_interface) & get_factory_item < ::draw2d::path >()
////   {
////
////      return ::factory::get_factory_item_array()->element_at_grow(e_factory_draw2d_path);
////
////   }
////
////
////   template < >
////   inline __pointer(factory_item_interface) & get_factory_item < ::draw2d::pen >()
////   {
////
////      return ::factory::get_factory_item_array()->element_at_grow(e_factory_draw2d_pen);
////
////   }
////
////
////   template < >
////   inline __pointer(factory_item_interface) & get_factory_item < ::draw2d::region >()
////   {
////
////      return ::factory::get_factory_item_array()->element_at_grow(e_factory_draw2d_region);
////
////   }
////
////
////} // namespace factory
////
//
//#include "device_lock.h"
//#include "lock.h"
//
//
//
