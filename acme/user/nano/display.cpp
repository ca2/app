//
// Created by camilo on 12/04-April/2022. 22:11 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "display.h"
#include "acme/parallelization/asynchronous.h"
#include "acme/parallelization/synchronous_lock.h"


namespace nano
{


   display::display()
   {

      defer_create_synchronization();

      if(!g_p)
      {

         g_p = this;

      }

   }


   display::~display()
   {


   }


   void display::kick_idle()
   {



   }


   void display::display_post(const ::procedure & procedure)
   {

      synchronous_lock synchronouslock(this->synchronization());

      m_procedureaPost.add(procedure);

      kick_idle();

   }


   void display::display_send(const ::procedure & procedure)
   {

      auto bIsCurrentBranch = is_branch_current();

      __matter_send_procedure(this, this, &display::display_post, procedure);

   }


   bool display::display_posted_routine_step()
   {

      synchronous_lock synchronouslock(this->synchronization());

      if (m_procedureaPost.has_element())
      {

         auto function = m_procedureaPost.pick_first();

         if (function)
         {

            synchronouslock.unlock();

            function();

            return true;

         }

      }

      return false;

   }


   ::size_i32 display::get_main_screen_size()
   {

      return { 800, 600 };

   }


} // namespace nano







