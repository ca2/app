#include "framework.h"
#include "core/user/simple/_simple.h"


simple_static::simple_static() :
   m_brushBkg(e_create)
{
   
   m_pimagelist = nullptr;
   
   m_bTransparent = false;
   
   m_brushBkg->m_etype = ::draw2d::brush::e_type_null;

}


simple_static::~simple_static()
{

}


void simple_static::pre_subclass_window()
{
   PreSubClassWindow();

   ::user::static_control::pre_subclass_window();
}


//LRESULT simple_static::OnSetIcon(wparam wparam, lparam lparam)
//{
//
//   if(m_pimagelist != nullptr)
//   {
//      
//      m_pimagelist->release();
//
//   }
//
//   return default_window_procedure(WM_SETICON, wparam, lparam);
//
//}


void simple_static::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   if (get_type() == type_icon)
   {

      ::draw2d::icon * picon = static_get_icon();

      if (picon != nullptr)
      {

         image_source imagesource(picon);

         rectangle_f64 rectangle(::point_i32(), ::size_i32(this->get_client_size().get_minimum_dimension()));

         image_drawing_options imagedrawingoptions(rectangle);

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

      }

   }
   else if (get_type() == type_text)
   {

      auto pstyle = get_style(pgraphics);

      pgraphics->set(get_font(pstyle));

      pgraphics->set_text_color(get_color(pstyle));

      string str;

      get_window_text(str);

      pgraphics->text_out(0, 0, str);

   }

}

