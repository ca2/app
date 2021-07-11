#include "framework.h" // previously aura/user/user.h
#include "aura/user/_user.h"


namespace aura
{



   draw_context::draw_context()
   {

   }


   void draw_context::get_client_rect(RECTANGLE_I32* lprectangle)
   {

      if (m_pdrawcontextNext)
      {

         m_pdrawcontextNext->get_client_rect(lprectangle);

      }
      else
      {

         *lprectangle = m_rectangleClient;

      }

   }


   bool draw_context::is_control_selected()
   {

      return m_bListItemSelected;

   }


   bool draw_context::is_control_hover()
   {

      return m_bListItemHover;

   }


   void draw_context::_001OnCustomDraw(::draw2d::graphics_pointer& pgraphics, ::user::interaction * puserinteraction)
   {

      pgraphics->chain(this);

      puserinteraction->_000OnDraw(pgraphics);

      pgraphics->unchain(this);

   }



} // namespace user



