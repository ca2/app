#pragma once


DECLARE_ENUMERATION(e_dock, enum_dock);
DECLARE_ENUMERATION(e_border, enum_border);
DECLARE_ENUMERATION(e_grip, enum_grip);


class image_frame_array;
class image_frame;
class colorref_array;



#if 0

CLASS_DECL_AURA bool TextOutU(HDC hdc, i32 x, i32 y, const ::string & pString, i32 ca);

CLASS_DECL_AURA bool GetTextExtentPoint32U(HDC hdc, const ::string & pString, i32 ca, LPSIZE32 psizl);

CLASS_DECL_AURA i32  DrawTextU(HDC hdc, const ::string & pchText, i32 cchText, RECTANGLE_I32 * lprc, ::u32 format);

#endif

CLASS_DECL_AURA void cra_from_quada(colorref_array & colorrefa, WINRGBQUAD * prgbquad, int iCount);


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


class image_extension;

class image_map;

class image_array;




#include "fwd.h"


#include "common.h"
#include "matrix.h"
#include "color_matrix.h"


#include "color_filter.h"


#include "_image.h"


#include "image_source.h"


#include "image_drawing.h"


#include "image_header.h"


#include "pixmap.h"



class CLASS_DECL_AURA save_image :
   virtual public ::matter
{
public:


   ::draw2d::e_format      m_eformat;
   int                     m_iQuality;
   int                     m_iDpi;


   save_image();


};


namespace draw2d
{


   class graphics;


   inline ::color::color get_pixel(const pixmap * ppixmap, int x, int y);


} // namespace draw2d


class image_frame;

class image_frame_array;



#include "object.h"
#include "keep.h"
#include "pen.h"
#include "bitmap.h"


#include "image_dynamic.h"
#include "image_meta.h"


#include "image_drawer.h"


#include "image.h"
#include "image_frame.h"
#include "image_array.h"
#include "image_frame_array.h"
#include "image_extension.h"
#include "image_map.h"
#include "image_map_ex1.h"


namespace draw2d
{

   CLASS_DECL_AURA void image_copy(::image * imagethis, ::image * pimage);
   CLASS_DECL_AURA void image_create(::object * pobject, ::image *& image);
   CLASS_DECL_AURA void image_create_image(::image * pimage, const ::size_i32 & size);
   CLASS_DECL_AURA unsigned int * image_get_data(::image * pimage);
   CLASS_DECL_AURA graphics * image_get_graphics(::image * pimage);


} // namespace draw2d




CLASS_DECL_AURA void draw_freetype_bitmap(::image * pm_p, i32 dx, i32 dy, void * pftbitmap, int x, int y);
CLASS_DECL_AURA void draw_freetype_bitmap(::image * pm_p, i32 dx, i32 dy, void * pftbitmap, int x, int y, byte a, byte rectangle, byte g, byte b);







#include "brush.h"
#include "palette.h"
#include "region.h"
#include "igui.h"


#include "aura/graphics/write_text/_.h"


#include "path.h"


#include "image_map.h"
#include "image_map_ex1.h"


#ifdef WINDOWS


namespace direct2d
{


   class plugin;


} // namespace draw2d_direct2d


#endif


#include "aura/graphics/write_text/drawer.h"


#include "aura/platform/draw_context2.h"
#include "graphics.h"


namespace draw2d
{


   class font_list;


} // namespace draw2d


#include "aura/windowing/cursor.h"
#include "aura/windowing/icon.h"


#include "cursor.h"
#include "icon.h"

#include "cursor_set.h"


#include "fastblur.h"
#include "imaging.h"
#include "image_list.h"
//#include "water_routine.h"

#include "api.h"
#include "graphics_extension.h"
#include "glyph.h"
#include "glyph_set.h"
//#include "font_enumeration.h"
//#include "fonts.h"
#include "image_palette.h"

#include "buffered_graphics.h"

#include "task_tool.h"

//#include "aura/platform/printer.h"

#include "printer.h"

#include "load_image.h"

#include "context_image.h"

#include "draw2d.h"



namespace factory
{


   template < >
   inline __pointer(factory_interface) & get_factory < ::draw2d::bitmap >()
   {

      return ::factory::get_factory_array()->element_at_grow(e_factory_draw2d_bitmap);

   }


   template < >
   inline __pointer(factory_interface) & get_factory < ::draw2d::brush >()
   {

      return ::factory::get_factory_array()->element_at_grow(e_factory_draw2d_brush);

   }


   template < >
   inline __pointer(factory_interface) & get_factory < ::write_text::font >()
   {

      return ::factory::get_factory_array()->element_at_grow(e_factory_draw2d_font);

   }


   template < >
   inline __pointer(factory_interface) & get_factory < ::draw2d::graphics >()
   {

      return ::factory::get_factory_array()->element_at_grow(e_factory_draw2d_graphics);

   }


   template < >
   inline __pointer(factory_interface) & get_factory < ::image >()
   {

      return ::factory::get_factory_array()->element_at_grow(e_factory_draw2d_image);

   }


   template < >
   inline __pointer(factory_interface) & get_factory < ::draw2d::path >()
   {

      return ::factory::get_factory_array()->element_at_grow(e_factory_draw2d_path);

   }


   template < >
   inline __pointer(factory_interface) & get_factory < ::draw2d::pen >()
   {

      return ::factory::get_factory_array()->element_at_grow(e_factory_draw2d_pen);

   }


   template < >
   inline __pointer(factory_interface) & get_factory < ::draw2d::region >()
   {

      return ::factory::get_factory_array()->element_at_grow(e_factory_draw2d_region);

   }


} // namespace factory


#include "device_lock.h"
#include "lock.h"



