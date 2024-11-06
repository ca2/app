//
//  track_popup_menu.h
//  aura
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on
//  2024-06-24 05:14 <3ThomasBorregaardSorensen!!
//
//
#pragma once


namespace menu
{

   enum enum_track_popup : int
   {
      
      e_track_popup_none,
      e_track_popup_inside_target = 1,
      e_track_popup_outside_target = 2,
      
   };


   DECLARE_ENUMERATION(e_track_popup, enum_track_popup);


   class CLASS_DECL_AURA track_popup :
      virtual public ::particle
   {
   public:
      

      ::pointer < ::menu::menu >          m_pmenu;
      ::pointer < ::user::interaction >   m_puserinteractionTarget;
      ::pointer < ::channel >             m_pchannelNotify;
      ::int_rectangle                     m_rectangleScreenHint;
      ::int_point                         m_pointCursorHint;
      ::menu::e_track_popup               m_etrackpopup;
      
      
      ::pointer < ::menu::menu >          m_pmenuImplementation;
      ::procedure                         m_procedureCompleted;
      
      
      track_popup(::menu::menu * pmenu,
                  ::user::interaction * puserinteractionTarget,
                  ::channel * pchannelNotify,
                  const ::int_point & pointCursorHint = {I32_MINIMUM,I32_MINIMUM},
                  const ::int_rectangle & rectangleScreenHint = {I32_MINIMUM, I32_MINIMUM, I32_MINIMUM, I32_MINIMUM},
                  ::menu::e_track_popup etrackpopup = {});
      
      virtual void track(const ::procedure & procedureFinished);
      
   };


} // namespace menu



