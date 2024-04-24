#include "framework.h"
#include "control_style.h"
#include "style.h"


namespace user
{


   control_style::control_style()
   {

      m_iUpdate = -1;

   }


   control_style::~control_style()
   {


   }

   
   bool control_style::is_up_to_date(::user::style * pstyle) const
   {

      return m_iUpdate == pstyle->m_iUpdate;

   }



   void control_style::update(::draw2d::graphics_pointer & pgraphics, style * pstyle, ::user::interaction * pinteraction)
   {

      m_iUpdate = pstyle->m_iUpdate;

      on_update(pgraphics, pstyle, pinteraction);

   }

   
   void control_style::on_update(::draw2d::graphics_pointer & pgraphics, style * pstyle, ::user::interaction * pinteraction)
   {


   }


} // namespace user



