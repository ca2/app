#include "framework.h"


namespace aura
{

   virtual ::e_status message_box(const char * pszMessage, const char * pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::future & process = ::future()) override;


   ::e_status system::os_application_system_run()
   {

      return ::success;

   }


} // namespace aura



