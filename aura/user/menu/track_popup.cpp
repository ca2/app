//
//  track_popup_menu.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on
//  2024-06-24 05:30 <3ThomasBorregaardSorensen!! ThomasLikesNumber5
//
#include "framework.h"
#include "track_popup.h"
#include "apex/user/menu/menu.h"
#include "aura/platform/application.h"


namespace menu
{


   track_popup::track_popup(::menu::menu * pmenu,
                            ::user::interaction * puserinteractionTarget,
                            ::channel * pchannelNotify,
                            const ::point_i32 & pointCursorHint,
                            const ::rectangle_i32 & rectangleScreenHint,
                            ::menu::e_track_popup etrackpopup):
   m_pmenu(pmenu),
   m_puserinteractionTarget(puserinteractionTarget),
   m_pchannelNotify(pchannelNotify),
   m_pointCursorHint(pointCursorHint),
   m_rectangleScreenHint(rectangleScreenHint),
   m_etrackpopup(etrackpopup)
   {
      
      initialize(m_pmenu);
      
   }


   void track_popup::track(const ::procedure & procedureCompleted)
   {
      
      m_procedureCompleted = procedureCompleted;
      
      application()->m_pauraapplication->track_popup_menu(this);
      
   }


} // namespace menu

