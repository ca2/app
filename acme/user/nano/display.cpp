//
// Created by camilo on 12/04-April/2022. 22:11 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "display.h"


namespace nano
{


   display * display::g_p = nullptr;


   display::display()
   {

      defer_create_mutex();

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

      synchronous_lock synchronouslock(mutex());

      m_procedureaPost.add(procedure);

      kick_idle();

   }


   void display::display_send(const ::procedure & procedure)
   {

      auto bIsCurrentBranch = is_branch_current();

      __send_procedure(this, &display::display_post, procedure);

   }


   bool display::display_posted_routine_step()
   {

      synchronous_lock synchronouslock(mutex());

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



} // namespace nano







