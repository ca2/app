//
// Created by camilo on 2026-04-27 19:07 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
//
#include "framework.h"
#include "accessibility.h"
#include "application.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"


namespace accessibility
{


   accessibility::accessibility()
   {


   }

   accessibility::~accessibility()
   {


   }


   ::pointer < ::accessibility::application > accessibility::process_identifier_application(::process_identifier processidentifier)
   {

      auto papplication = createø < ::accessibility::application >();

      papplication->open_by_process_identifier(processidentifier);

      return papplication;

   }


   ::pointer < ::accessibility::application > accessibility::module_path_application(const ::scoped_string & scopedstr)
   {

      auto papplication = createø < ::accessibility::application >();

      papplication->open_by_module_path(scopedstr);

      return papplication;

   }


   ::pointer<::accessibility::application>
   accessibility::application_predicate(const ::function<bool(::accessibility::application *papplication)> &function)
   {

      auto processidentifiera = node()->processes_identifiers();

      for (auto & processidentifier : processidentifiera)
      {

         auto papplication = createø < ::accessibility::application >();

         papplication->open_by_process_identifier(processidentifier);

         if (function(papplication))
         {

            return papplication;

         }

      }

      return nullptr;

   }



   //::pointer<::accessibility::application> accessibility::module_path_application(const ::scoped_string &scopestr)
   //{

   //   return{};

   //}


   //::pointer<::accessibility::application>
   //accessibility::process_identifier_application(
   //   ::process_identifier processidentifier)
   //{
   //   return{};
   //}


   //::pointer<::accessibility::application>
   //accessibility::application_predicate(const ::function<bool(::accessibility::application *papplication)> &function)
   //{
   //   return{};
   //}



} // namespace accessibility



