//
// Created by camilo on 2026-04-06 10:50 <3ThomasBorregaardSørensen!!
//



// Offloading apex(TBS)::app_core from deep stack stuff into acme(CSTBS) ::system 2022-02-22 by camilo at 07:19 <3ThomasBorregaardSorensen!!
#pragma once


#include "subsystem/subsystem.h"


namespace innate_subsystem
{


   class CLASS_DECL_INNATE_SUBSYSTEM subsystem :
      virtual public ::subsystem::subsystem
   {
   public:


      static ::innate_subsystem::subsystem *            s_p;

      ::pointer < ::innate_subsystem::resource_loader > m_presourceloader;
      ::pointer < ::innate_subsystem::SystemMetricsInterface > m_psystemmetrics;
      ::pointer<::innate_subsystem::KeyboardLayoutInterface> m_pkeyboardlayout;

      ::map_base < ::operating_system::window, ::pointer < ::innate_subsystem::WindowInterface > > m_mapWindow;

      subsystem();
      ~subsystem() override;


      ::innate_subsystem::resource_loader* ResourceLoader();

      ::innate_subsystem::KeyboardLayoutInterface *keyboard_layout();


      int message_box(
         const ::user_interaction_sink & userinteractionsink,
         const ::scoped_string & scopedstrMessage,
         const ::scoped_string & scopedstrCaption,
         unsigned int uType) override;


      virtual ::innate_subsystem::SystemMetricsInterface * metrics();

      virtual ::user::enum_key virtual_key_code_to_user_key(int iVirtualKeyCode);


      virtual ::pointer < ::innate_subsystem::WindowInterface > getWindow(const ::operating_system::window & window);
      virtual void setWindow(const ::operating_system::window & window, ::innate_subsystem::WindowInterface * pwindow);


   };



} // namespace innate_subsystem



inline ::innate_subsystem::subsystem * main_innate_subsystem()
{

   if (!::innate_subsystem::subsystem::s_p)
   {

      system()->MainSubsystem();

   }

   return ::innate_subsystem::subsystem::s_p;

}

