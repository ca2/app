//
// Created by camilo on 2026-04-05 03:03 <3ThomasBorregaardSørensen!!
//


// Offloading apex(TBS)::app_core from deep stack stuff into acme(CSTBS) ::system 2022-02-22 by camilo at 07:19 <3ThomasBorregaardSorensen!!
#pragma once




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

   };



} // namespace subsystem



inline ::subsystem::subsystem * main_subsystem()
{

   if (!::subsystem::subsystem::s_p)
   {

      system()->subsystem();

   }

   return ::subsystem::subsystem::s_p;

}

