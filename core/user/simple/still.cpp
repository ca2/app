#include "framework.h"
#include "still.h"
#include "aura/graphics/image/icon.h"
#include "aura/graphics/image/drawing.h"


simple_still::simple_still()
{
   
   m_pimagelist = nullptr;
   
   m_bTransparent = false;
   
   //m_pbrushBkg->m_etype = ::draw2d::brush::e_type_null;

}


simple_still::~simple_still()
{

}


void simple_still::pre_subclass_window()
{
   
   PreSubClassWindow();

   ::user::still::pre_subclass_window();

}


//LRESULT simple_still::OnSetIcon(wparam wparam, lparam lparam)
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


void simple_still::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
{

   if (get_still_type() == ::user::e_still_icon)
   {

      ::draw2d::icon * picon = still_get_icon();

      if (picon != nullptr)
      {

         image_source imagesource(picon);

         rectangle_f64 rectangle(::point_i32(), ::size_i32(this->get_client_size().get_minimum_dimension()));

         image_drawing_options imagedrawingoptions(rectangle);

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

      }

   }
   else if (get_still_type() == ::user::e_still_text)
   {

      auto pstyle = get_style(pgraphics);

      pgraphics->set(get_font(pstyle));

      pgraphics->set_text_color(get_color(pstyle));

      auto strWindowText = get_window_text();

      //get_window_text(str);

      pgraphics->text_out(0, 0, strWindowText);

   }

}

