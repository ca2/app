//
// Created by camilo on 2026-04-06 10:50 <3ThomasBorregaardSørensen!!
//



// Offloading apex(TBS)::app_core from deep stack stuff into acme(CSTBS) ::system 2022-02-22 by camilo at 07:19 <3ThomasBorregaardSorensen!!
#pragma once


#include "subsystem/subsystem.h"


namespace subsystem_apex
{


   class CLASS_DECL_INNATE_SUBSYSTEM subsystem :
      virtual public ::subsystem::subsystem
   {
   public:


      static ::subsystem_apex::subsystem *            s_p;

      ::pointer < ::subsystem_apex::resource_loader > m_presourceloader;
      ::pointer < ::subsystem_apex::SystemMetricsInterface > m_psystemmetrics;

      subsystem();
      ~subsystem() override;


      ::subsystem_apex::resource_loader* resource_loader();


      int message_box(
         const ::user_interaction_sink & userinteractionsink,
         const ::scoped_string & scopedstrMessage,
         const ::scoped_string & scopedstrCaption,
         unsigned int uType) override;


      virtual ::subsystem_apex::SystemMetricsInterface * metrics();

      virtual ::user::enum_key virtual_key_code_to_user_key(int iVirtualKeyCode);

   };



} // namespace subsystem_apex



inline ::subsystem_apex::subsystem * main_innate_subsystem()
{

   if (!::subsystem_apex::subsystem::s_p)
   {

      system()->subsystem();

   }

   return ::subsystem_apex::subsystem::s_p;

}

