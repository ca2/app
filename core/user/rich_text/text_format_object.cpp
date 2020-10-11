#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/user/rich_text/_rich_text.h"
#endif
#include "text_format_object.h"


namespace user
{


   text_format_object::text_format_object()
   {

   }


   text_format_object::~text_format_object()
   {

   }


   void text_format_object::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->fill_rect(m_rect, ARGB(127, 255, 255, 180));
      pgraphics->draw_text(m_str, m_rect, e_align_center);
      ::rect rect(m_rect);
      pgraphics->draw_rect(rect, ARGB(127, 255, 255, 255));
      rect.deflate(1, 1);
      pgraphics->draw_rect(rect, ARGB(127, 255, 255, 255));

   }


} // namespace user



