//
//  track_popup_menu.cpp
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on
//  2024-06-24 05:30 <3ThomasBorregaardSorensen!! ThomasLikesNumber5
//
#include "framework.h"
#include "track_popup_menu.h"


track_popup_menu::track_popup_menu(::user::interaction * puserinteraction,
                 const ::scoped_string & scopedstrXml,
                 const ::point_i32 & pointScreenHint,
                 const e_track_popup_menu & etrackpopupmenu):
m_puserinteraction(puserinteraction),
m_strXml(scopedstrXml),
m_pointScreenHint(pointScreenHint),
m_etrackpopupmenu(etrackpopupmenu)
{
   
   
}


void track_popup_menu::post_start()
{
   
   application()->track_popup_menu(this);
   
}
