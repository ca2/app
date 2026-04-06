//
// Created by camilo on 2026-04-06 10:50 <3ThomasBorregaardSørensen!!
//



// Offloading apex(TBS)::app_core from deep stack stuff into acme(CSTBS) ::system 2022-02-22 by camilo at 07:19 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/subsystem/subsystem.h"


namespace innate_subsystem
{


   class CLASS_DECL_APEX subsystem :
      virtual public ::subsystem::subsystem
   {
   public:


      static ::subsystem::subsystem *            s_p;
      ::pointer < ::subsystem::string_table >     m_pstringtable;
      ::pointer < ::subsystem::resource_loader >     m_presourceloader;
      ::pointer < ::subsystem::Registry >     m_pregistry;
      ::pointer < ::subsystem::Shell >     m_pshell;

      subsystem();
      ~subsystem() override;


      virtual ::subsystem::string_table * string_table();
      virtual ::subsystem::resource_loader* resource_loader();
      virtual ::subsystem::Registry* registry();
      virtual ::subsystem::Shell* shell();

      /**
       * Creates SID from sid string.
       * @return created SID.
       * @throws SystemException on fail.
       */
      virtual ::pointer < ::subsystem::SecurityIdentifier > createSidFromString(const ::scoped_string & scopedstr);



      virtual int message_box(
         WindowInterface * pwindow,
         const ::scoped_string & scopedstrMessage,
         const ::scoped_string & scopedstrCaption,
         UINT uType);



   };



} // namespace innate_subsystem



inline ::innate_subsystem::subsystem * innate_subsystem()
{

   if (!::innate_subsystem::subsystem::s_p)
   {

      system()->subsystem();

   }

   return ::innate_subsystem::subsystem::s_p;

}

