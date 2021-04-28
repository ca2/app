#include "framework.h" 
#include "core/user/simple_ui/_simple_ui.h"

namespace simple_ui
{


   label::label()
   {

   }

   label::~label()
   {
   }




   void label::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);


      color32_t c;

      //if(get_style()->m_eschema == ::hotplugin::plugin::schema_darker)
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS
         c = argb(255, 114, 149 + 49, 177 + 49);
#else
         c = argb(255, 149 + 49, 1140, 123 + 49);
#endif

      }
      //else
      {

#if CA2_PLATFORM_VERSION == CA2_BASIS
         c = argb(255, 90, 50, 80);
#else
         c = argb(255, 49, 90, 23);
#endif

      }

      ::rectangle_i32 rectClient;

      get_client_rect(rectClient);

      ::draw2d::brush_pointer b(e_create);

      b->create_solid(c);

      ::write_text::font_pointer f(e_create);

      /*f->create_pixel_font(pnode->font_name(e_font_sans_ex), (i32)rectClient.height() * 0.7);

      float fMargin = (rectClient.height() * ((1.0f - 0.7f) / 2.0f));*/

      f->create_pixel_font(pnode->font_name(e_font_sans), (i32)rectClient.height() * .84);

      float fMargin = 0.0;

      pgraphics->set(f);

      pgraphics->set(b);

      string strText;

      get_window_text(strText);

      pgraphics->text_out(rectClient.left, (i32)(rectClient.top + fMargin), strText);

   }


} // namespace simple_ui
