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


      ::pointer_array<::particle>      m_particleaMouseHandler;
      ::pointer_array<::particle>      m_particleaKeyboardHandler;


      ::task_pointer                   m_ptaskInput;


      input();
      ~input() override;



      virtual void defer_input();

      virtual void __input_task();


      virtual bool needs_input();


      virtual ::e_status is_keyboard_message_handling_enabled(::user::primitive * puserprimitiveEnablePrompt);

      virtual void add_keyboard_message_handler(::particle * pparticle);
      virtual void erase_keyboard_message_handler(::particle * pparticle);

      virtual ::e_status is_mouse_message_handling_enabled(::user::primitive * puserprimitiveEnablePrompt);

      virtual void add_mouse_message_handler(::particle * pparticle);
      virtual void erase_mouse_message_handler(::particle * pparticle);


      virtual void install_mouse_hook(::particle * pparticle, ::user::primitive * puserprimitiveEnablePrompt);
      virtual void install_keyboard_hook(::particle * pparticle, ::user::primitive * puserprimitiveEnablePrompt);


   };


} // namespace input



