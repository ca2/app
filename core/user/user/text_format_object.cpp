// From design/text_format/user_text_format_object.cpp by camilo on
// 2022-09-04 00:17 <3ThomasBorregaardSorensen!!
#include "platform.h"
#include "text_format_object.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/graphics_pointer.h"


namespace user
{


   text_format_object::text_format_object()
   {


      string               m_str = "Night1";

   }



   text_format_object::~text_format_object()
   {

   }


   void text_format_object::_001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics)
   {

      pdraw2dgraphics->fill_rectangle(m_rectangle, argb(127, 255, 255, 180));
      pdraw2dgraphics->draw_text(m_str, m_rectangle, e_align_center);
      ::i32_rectangle rectangle(m_rectangle);
      pdraw2dgraphics->draw_inset_rectangle(rectangle, argb(127, 255, 255, 255), 1.0);
      rectangle.deflate(1, 1);
      pdraw2dgraphics->draw_inset_rectangle(rectangle, argb(127, 255, 255, 255), 1.0);

   }


} // namespace user



