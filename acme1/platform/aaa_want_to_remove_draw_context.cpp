#include "framework.h" // previously acme/user/user.h


namespace acme
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



