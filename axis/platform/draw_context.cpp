#include "framework.h" // previously aura/user/user.h


namespace axis
{



   draw_context::draw_context()
   {

   }


   bool draw_context::is_control_selected()
   {

      return m_bListItemSelected;

   }


   bool draw_context::is_control_hover()
   {

      return m_bListItemHover;

   }


} // namespace user



