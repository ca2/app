#include "framework.h"


namespace aura
{

   virtual void message_box(const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const ::future & future = ::future()) override;


   void system::os_application_system_run()
   {

      return ::success;

   }


} // namespace aura



