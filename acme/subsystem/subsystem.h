//
// Created by camilo on 2026-04-05 03:03 <3ThomasBorregaardSørensen!!
//


// Offloading apex(TBS)::app_core from deep stack stuff into acme(CSTBS) ::system 2022-02-22 by camilo at 07:19 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/handler/handler.h"
//#include "acme/platform/ini.h"
#include "acme/platform/system_acme.h"
#include "acme/platform/system_apex.h"
#include "acme/platform/system_aqua.h"
#include "acme/platform/system_aura.h"
#include "acme/platform/system_axis.h"
#include "acme/platform/system_core.h"


namespace subsystem
{


   class CLASS_DECL_ACME subsystem :
      virtual public ::particle
   {
   public:


      static ::subsystem::subsystem *            s_p;
      ::pointer < ::subsystem::string_table >     m_pstringtable;
      ::pointer < ::subsystem::resource_loader >     m_presourceloader;
      ::pointer < ::subsystem::Registry >     m_pregistry;

      subsystem();
      ~subsystem() override;


      virtual ::subsystem::string_table * string_table();
      virtual ::subsystem::resource_loader* resource_loader();
      virtual ::subsystem::Registry* registry();


   };



} // namespace subsystem



inline ::subsystem::subsystem * main_subsystem()
{

   return ::subsystem::subsystem::s_p;

}

