// From scroll.h by camilo on 2022-08-27 13:42 <3ThomasBorregaardSorensen!!
#pragma once


#include "interaction.h"
#include "style.h"


namespace user
{


   template < typename CONTROL_STYLE >
   void style::get(::pointer<CONTROL_STYLE>& pcontrolstyleImpl, ::draw2d::graphics_pointer & pgraphics, ::user::interaction * pinteraction)
   {

      auto & pcontrolstyle = m_controlstyle[pinteraction->m_econtroltype];

      if (!pcontrolstyle)
      {

         pcontrolstyle = __new(CONTROL_STYLE);

      }

      if (!pcontrolstyle->is_up_to_date(this))
      {

         pcontrolstyle->update(pgraphics, this, pinteraction);

      }

      pcontrolstyleImpl = pcontrolstyle;

   }


} // namespace user



