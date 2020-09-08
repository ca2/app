#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


namespace user
{




   bool style_base::_001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics, ::user::split_layout * psplitlayout)
   {

      return false;

   }


   e_control_type style_base::get_control_type() const
   {

      return control_type_none;

   }


   ::color style_base::get_color(const ::user::interaction* pinteraction, ::user::e_element eelement, ::user::estate estate) const
   {

      if (::is_set(pinteraction))
      {

         auto econtroltype = pinteraction->get_control_type();

         if (econtroltype == ::user::control_type_list)
         {

            if (eelement == ::user::element_background)
            {

               return ::color(0, 0, 0, 0);

            }

         }

      }

      return ::color();

   }


} // namespace user











