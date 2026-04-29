// From tvnc by camilo on 2026-04-24 11:08 <3ThomasBorregaardSørensen!!
#pragma once


#include "acme/constant/user_message.h"


namespace subsystem
{


   class CLASS_DECL_SUBSYSTEM WindowMessageHandler :
   virtual public ::particle
   {
   public:
      
      WindowMessageHandler();
      ~WindowMessageHandler() override;

      // This function must return true if a message has been processed.
      virtual bool processMessage(::user::enum_message eusermessage, ::wparam wparam, ::lparam lparam);


   };


} // namespace subsystem




