//
// Created by camilo on 2026-04-05 20:14 <3ThomasBorregaardSørensen!!
//


// Offloading apex(TBS)::app_core from deep stack stuff into acme(CSTBS) ::system 2022-02-22 by camilo at 07:19 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/subsystem/subsystem.h"
#include "acme/operating_system/windows/subsystem/_common_header.h"


namespace windows
{
   namespace subsystem
   {


      class CLASS_DECL_ACME subsystem :
         virtual public ::subsystem::subsystem
      {
      public:


         static ::windows::subsystem::subsystem *            s_p;
         // ::pointer < ::subsystem::string_table >     m_pstringtable;
         // ::pointer < ::subsystem::resource_loader >     m_presourceloader;
         // ::pointer < ::subsystem::Registry >     m_pregistry;
         // ::pointer < ::subsystem::Shell >     m_pshell;

          ::pointer < ::windows::WTS > m_pwts;

         subsystem();
         ~subsystem() override;

         //
         // virtual ::subsystem::string_table * string_table();
         // virtual ::subsystem::resource_loader* resource_loader();
         // virtual ::subsystem::Registry* registry();
         virtual ::windows::WTS* wts();

         ::pointer < ::subsystem::SecurityIdentifier > createSidFromString(const ::scoped_string & scopedstr) override;

      };



   } // namespace subsystem
} // namespace windows



inline ::windows::subsystem::subsystem * windows_subsystem()
{

   return ::windows::subsystem::subsystem::s_p;

}

