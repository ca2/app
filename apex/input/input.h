//
// Created by camilo on 9/18/23  14:47 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/platform/department.h"


namespace input
{


   class input :
      virtual public ::acme::department
   {
   public:


      input();
      ~input() override;


      virtual ::e_status is_keyboard_message_handling_enabled(::user::primitive * puserprimitiveEnablePrompt);

      virtual void add_keyboard_message_handler(::particle * pparticle);
      virtual void erase_keyboard_message_handler(::particle * pparticle);

      virtual ::e_status is_mouse_message_handling_enabled(::user::primitive * puserprimitiveEnablePrompt);

      virtual void add_mouse_message_handler(::particle * pparticle);
      virtual void erase_mouse_message_handler(::particle * pparticle);


   };


} // namespace input



