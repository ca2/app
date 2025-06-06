#include "framework.h"
#include "still.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/image/icon.h"
#include "aura/graphics/image/drawing.h"


simple_still::simple_still()
{
   
   //m_pimagelist = nullptr;
   
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

      ::image::icon * picon = still_get_icon();

      if (picon != nullptr)
      {

         ::image::image_source imagesource(picon);
         
         auto minimum_dimension = this->get_client_size().minimum();
         
         ::double_size size(minimum_dimension);

         double_rectangle rectangle(::double_point(), size);

         ::image::image_drawing_options imagedrawingoptions(rectangle);

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

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

