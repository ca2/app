#include "framework.h"


namespace aura
{

   
   ::estatus system::message_box(const char * pszMessage, const char * pszTitle, const ::e_message_box & emessagebox, const promise::process & process)
   {

      return os_message_box(pszMessage, pszTitle, emessagebox, process);

   }

   ::estatus system::message_box_timeout(const char * pszMessage, const char * pszTitle, const ::duration & durationTimeout, const ::e_message_box & emessagebox, const promise::process & process)
   {

      return os_message_box(pszMessage, pszTitle, emessagebox, process);

   }


   ::estatus system::os_application_system_run()
   {

      return ::success;

   }


} // namespace aura



