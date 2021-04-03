#include "framework.h"


namespace sphere
{


   main_frame::main_frame(::object * pobject) :
      ::object(pobject),
      simple_frame_window(pobject),
      simple_main_frame(pobject)
   {

      window_enable_full_screen();

      //create_translucency(::user::e_element_none, ::user::e_translucency_none);

   }


   main_frame::~main_frame()
   {

   }


   //bool main_frame::get_translucency(::user::enum_translucency & etranslucency, ::user::enum_element eelement, ::user::style_context * pcontext)
   //{

   //   etranslucency = ::user::e_translucency_present;

   //   return true;

   //}


   //bool main_frame::get_color(color32_t & cr, ::user::e_color ecolor, ::user::style_context * pcontext)
   //{

   //   bool bOk = true;

   //   if (ecolor == ::user::color_text || ecolor == ::user::color_edit_text)
   //   {

   //      cr = papplication->get_theme_fg_color();

   //   }
   //   else if (ecolor == ::user::color_text_selected)
   //   {

   //      cr = argb(255, 255, 255, 255);

   //   }
   //   else if (ecolor == ::user::color_text_highlight)
   //   {

   //      cr = argb(255, 55, 105, 255);

   //   }
   //   else if (ecolor == ::user::color_text_selected_highlight)
   //   {

   //      cr = argb(255, 102, 153, 255);

   //   }
   //   else if (ecolor == ::user::color_background
   //            || ecolor == ::user::color_edit_background
   //            || ecolor == ::user::color_toolbar_background)
   //   {


   //      cr = papplication->get_theme_bg_color();

   //   }
   //   else if (ecolor == ::user::color_background_selected)
   //   {

   //      if (_001IsTranslucent())
   //      {

   //         cr = argb(190, 0, 0, 127);

   //      }
   //      else
   //      {

   //         cr = argb(255, 0, 0, 127);

   //      }

   //   }
   //   else if (ecolor == ::user::color_background_selected)
   //   {

   //      if (_001IsTranslucent())
   //      {

   //         cr = argb(190, 0, 0, 127);

   //      }
   //      else
   //      {

   //         cr = argb(255, 0, 0, 127);

   //      }

   //   }
   //   else if (ecolor == ::user::color_border)
   //   {

   //      cr = argb(255, 90, 90, 80);

   //   }
   //   else if (ecolor == ::user::color_border_hover)
   //   {

   //      cr = argb(255, 90, 190, 80);

   //   }
   //   else if (ecolor == ::user::color_text_hover)
   //   {

   //      cr = argb(255, 90, 184, 255);

   //   }
   //   else
   //   {

   //      bOk = false;

   //   }

   //   return bOk;

   //}


   bool main_frame::has_pending_graphical_update()
   {

      return is_window_visible();

   }


} // namespace sphere



