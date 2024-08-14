// Created by camilo on 2024-08-09 14:34 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/conversation_message.h"


namespace operating_system
{


   class CLASS_DECL_ACME console_message_box :
      virtual public ::conversation_message
   {
   public:


      console_message_box();
      ~console_message_box() override;
      
      ::payload do_synchronously(const class time & timeWait = ::time::infinity()) override;


   };


} // namespace operating_system



