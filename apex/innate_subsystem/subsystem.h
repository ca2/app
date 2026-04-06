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


      static ::innate_subsystem::subsystem *            s_p;

      subsystem();
      ~subsystem() override;


      virtual int message_box(
         WindowInterface * pwindow,
         const ::scoped_string & scopedstrMessage,
         const ::scoped_string & scopedstrCaption,
         unsigned int uType);



   };



} // namespace innate_subsystem



inline ::innate_subsystem::subsystem * main_innate_subsystem()
{

   if (!::innate_subsystem::subsystem::s_p)
   {

      system()->subsystem();

   }

   return ::innate_subsystem::subsystem::s_p;

}

