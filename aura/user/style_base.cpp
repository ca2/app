#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


namespace user
{


   style_base::style_base()
   {


   }


   style_base::~style_base()
   {


   }



   bool style_base::_001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics, ::user::split_layout * psplitlayout)
   {

      return false;

   }


   bool style_base::_001OnDrawMainFrameBackground(::draw2d::graphics_pointer & pgraphics,::user::frame * pframe)
   {

      return false;

   }


   bool style_base::draw_check(::user::interaction * pinteraction, ::enum_check echeck, const ::rectangle_i32 & rectangle, ::draw2d::graphics_pointer & pgraphics)
   {

      return false;

   }


   bool style_base::simple_ui_draw_focus_rect(::user::interaction * pinteraction,::draw2d::graphics_pointer & pgraphics)
   {

      return false;

   }


   bool style_base::_001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem, ::user::toolbar * ptoolbar)
   {

      return false;

   }


   bool style_base::_001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar)
   {

      return false;

   }


   bool style_base::_001DrawScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar)
   {

      return false;

   }


   enum_control_type style_base::get_control_type() const
   {

      return e_control_type_none;

   }


   ::color::color style_base::get_color(const ::user::interaction* pinteraction, ::user::enum_element eelement, ::user::enum_state estate) const
   {

      if (::is_set(pinteraction))
      {

         auto econtroltype = pinteraction->get_control_type();

         if (econtroltype == ::user::e_control_type_list)
         {

            if (eelement == ::user::e_element_background)
            {

               return ::color::color(0, 0, 0, 0);

            }

         }

      }

      return ::color::color();

   }


   bool style_base::get_int(const ::user::interaction * pinteraction, int & i, ::user::enum_int eint, ::user::enum_state estate) const
   {

      return false;

   }


   bool style_base::get_double(const ::user::interaction* pinteraction, double & d, ::user::enum_double edouble, ::user::enum_state estate) const
   {

      return false;

   }


} // namespace user











