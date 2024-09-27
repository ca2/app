//
// Created by camilo on 9/18/23 15:07 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "input.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/task.h"
#include "acme/platform/application.h"


namespace input
{


   input::input()
   {


   }


   input::~input()
   {


   }


   ::e_status input::is_keyboard_message_handling_enabled(::user::prototype * puserprimitiveEnablePrompt)
   {

      return ::success;

   }



   ::e_status input::is_mouse_message_handling_enabled(::user::prototype * puserprimitiveEnablePrompt)
   {

      return ::success;

   }


   void input::defer_input()
   {

      if(needs_input())
      {

         if (m_ptaskInput)
         {

            return;

         }

         m_ptaskInput = app_fork([this]()
                                    {

            __input_task();



                                    });

      }
      else
      {

         if (m_ptaskInput)
         {

            m_ptaskInput->set_finish();

            m_ptaskInput.release();

         }

      }

   }


   void input::__input_task()
   {


   }


   bool input::needs_input()
   {

      return m_particleaMouseHandler.has_element() || m_particleaKeyboardHandler.has_element();

   }


   void input::add_mouse_message_handler(::particle * pparticle)
   {

      {

         synchronous_lock synchronouslock(this->synchronization());

         m_particleaMouseHandler.add(pparticle);

      }

      defer_input();

   }


   void input::add_keyboard_message_handler(::particle * pparticle)
   {

      {

         synchronous_lock synchronouslock(this->synchronization());

         m_particleaKeyboardHandler.add(pparticle);

      }

      defer_input();

   }


   void input::erase_mouse_message_handler(::particle * pparticle)
   {

      {

         synchronous_lock synchronouslock(this->synchronization());

         m_particleaMouseHandler.erase(pparticle);

      }

      defer_input();

   }


   void input::erase_keyboard_message_handler(::particle * pparticle)
   {

      {

         synchronous_lock synchronouslock(this->synchronization());

         m_particleaKeyboardHandler.erase(pparticle);

      }

      defer_input();

   }


   void input::install_mouse_hook(::particle * pparticle, ::user::prototype * puserprimitiveEnablePrompt)
   {

      auto estatus = is_mouse_message_handling_enabled(puserprimitiveEnablePrompt);

      if(estatus != ::success)
      {

         throw ::exception(error_not_supported, "mouse message handling not enabled for the application : " + application()->application_name());

      }

      add_mouse_message_handler(pparticle);

   }


   void input::install_keyboard_hook(::particle * pparticle, ::user::prototype * puserprimitiveEnablePrompt)
   {

      auto estatus = is_keyboard_message_handling_enabled(puserprimitiveEnablePrompt);

      if(estatus != ::success)
      {

         throw ::exception(error_not_supported, "keyboard message handling not enabled for the application : " + application()->application_name());

      }

      add_keyboard_message_handler(pparticle);

   }


} // namespace input



