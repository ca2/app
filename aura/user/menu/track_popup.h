//
//  track_popup_menu.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on
//  2024-06-24 05:14 <3ThomasBorregaardSorensen!!
//
//
#pragma once


enum enum_track_popup_menu : i32
{
  
   e_track_popup_menu_none,
   
};


DECLARE_ENUMERATION(e_track_popup_menu, enum_track_popup_menu);


class CLASS_DECL_AURA track_popup_menu :
   virtual public ::particle
{
public:
   
   ::pointer < ::user::interaction >   m_puserinteraction;
   ::string                            m_strXml;
   ::pointer < ::application_menu >    m_papplicationmenu;
   ::pointer < ::user::menu_item >     m_pmenuitem;
   ::point_i32                         m_pointScreenHint = ::point_i32(I32_MINIMUM, I32_MINIMUM);
   ::e_track_popup_menu                m_etrackpopupmenu = {};
   ::pointer < ::user::interaction >   m_pinteractionMenu;
   
   track_popup_menu(::user::interaction * puserinteraction,
                    const ::scoped_string & scopedstrXml,
                    const ::point_i32 & pointScreenHint = ::point_i32(I32_MINIMUM, I32_MINIMUM),
                    const e_track_popup_menu & etrackpopupmenu = {});
  
   track_popup_menu(::user::interaction * puserinteraction,
                    ::application_menu * papplicationmenu,
                    const ::point_i32 & pointScreenHint = ::point_i32(I32_MINIMUM, I32_MINIMUM),
                    const e_track_popup_menu & etrackpopupmenu = {});
  
   track_popup_menu(::user::interaction * puserinteraction,
                    const ::scoped_string & scopedstrXml,
                    const ::point_i32 & pointScreenHint = ::point_i32(I32_MINIMUM, I32_MINIMUM),
                    const e_track_popup_menu & etrackpopupmenu = {});
  
   virtual void post_start();
   
};
