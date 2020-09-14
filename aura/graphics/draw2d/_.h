#pragma once


using edock = cflag < e_dock >;
using eborder = cflag < e_border >;
using egrip = cflag < e_grip >;


class image_frame_array;
class image_frame;
class colorref_array;


CLASS_DECL_AURA bool TextOutU(HDC hdc, i32 x, i32 y, const char * pString, i32 ca);

CLASS_DECL_AURA bool GetTextExtentPoint32U(HDC hdc, const char * pString, i32 ca, LPSIZE psizl);

CLASS_DECL_AURA i32  DrawTextU(HDC hdc, const char * pchText, i32 cchText, RECT * lprc, UINT format);

//CLASS_DECL_AURA bool draw2d_gif_load_frame(::image * pimageCanvas, image_frame_array * pframea, image_frame * pframe, int uFrameIndex, u8 * ba, int iScan, colorref_array & cra, int transparentIndex);

CLASS_DECL_AURA void cra_from_quada(colorref_array & colorrefa, RGBQUAD * prgbquad, int iCount);


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


CLASS_DECL_AURA COLORREF make_colorref(i32 a, i32 rect, i32 g, i32 b);


inline byte clampAndConvert(double v)
{


   if (v < 0)
      return 0;
   if (v > 255)
      return 255;
   return (byte)(v);


}


#include "fwd.h"


#include "common.h"
#include "matrix.h"
#include "color.h"
#include "color_matrix.h"
#include "colorref_array.h"


#include "_image.h"


#include "image_header.h"


#include "pixmap.h"



class CLASS_DECL_AURA save_image
{
public:


   ::draw2d::e_format      m_eformat;
   int                     m_iQuality;
   int                     m_iDpi;


   save_image();
   save_image(const ::var & varFile, const ::var & varOptions);


};


namespace draw2d
{


   class graphics;


   inline COLORREF get_pixel(const pixmap* ppixmap, int x, int y);


} // namespace draw2d


class image_frame;

class image_frame_array;



#include "object.h"
#include "keep.h"
#include "pen.h"
#include "bitmap.h"


#include "image_dynamic.h"
#include "image_meta.h"


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
   CLASS_DECL_AURA void image_create(::object * pobject, ::image * & image);
   CLASS_DECL_AURA void image_create_image(::image * pimage,  const ::size & size);
   CLASS_DECL_AURA unsigned int * image_get_data(::image * pimage);
   CLASS_DECL_AURA graphics * image_get_graphics(::image * pimage);


} // namespace draw2d




CLASS_DECL_AURA void draw_freetype_bitmap(::image * pm_p, i32 dx, i32 dy, void * pftbitmap, int x, int y);
CLASS_DECL_AURA void draw_freetype_bitmap(::image * pm_p, i32 dx, i32 dy, void * pftbitmap, int x, int y, byte a, byte rect, byte g, byte b);







#include "brush.h"
#include "font.h"
#include "palette.h"
#include "region.h"
#include "igui.h"
#include "path.h"



#include "image_map.h"
#include "image_map_ex1.h"




//namespace aura
//{
//
//
//   class str_context;
//
//
//}


#include "aura/platform/draw_context2.h"
#include "graphics.h"


namespace draw2d
{


   class font_list;


} // namespace draw2d


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
#include "font_enumeration.h"
#include "font_department.h"
#include "image_palette.h"

#include "buffered_graphics.h"

#include "thread_tool.h"

//#include "aura/platform/printer.h"

#include "printer.h"

#include "context_image.h"

#include "draw2d.h"



namespace factory
{


   template < >
   inline __pointer(factory_interface) & get_factory < ::draw2d::bitmap >()
   {

      return g_pfactorya->element_at_grow(factory_draw2d_bitmap);

   }


   template < >
   inline __pointer(factory_interface) & get_factory < ::draw2d::brush >()
   {

      return g_pfactorya->element_at_grow(factory_draw2d_brush);

   }


   template < >
   inline __pointer(factory_interface) & get_factory < ::draw2d::font >()
   {

      return g_pfactorya->element_at_grow(factory_draw2d_font);

   }


   template < >
   inline __pointer(factory_interface) & get_factory < ::draw2d::graphics >()
   {

      return g_pfactorya->element_at_grow(factory_draw2d_graphics);

   }


   template < >
   inline __pointer(factory_interface) & get_factory < ::image >()
   {

      return g_pfactorya->element_at_grow(factory_draw2d_image);

   }


   template < >
   inline __pointer(factory_interface) & get_factory < ::draw2d::path >()
   {

      return g_pfactorya->element_at_grow(factory_draw2d_path);

   }


   template < >
   inline __pointer(factory_interface) & get_factory < ::draw2d::pen >()
   {

      return g_pfactorya->element_at_grow(factory_draw2d_pen);

   }


   template < >
   inline __pointer(factory_interface) & get_factory < ::draw2d::region >()
   {

      return g_pfactorya->element_at_grow(factory_draw2d_region);

   }


} // namespace factory



