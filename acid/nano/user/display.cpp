//
// Created by camilo on 12/04-April/2022. 22:11 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "display.h"
#include "acid/parallelization/asynchronous.h"
#include "acid/parallelization/synchronous_lock.h"
#include "acid/primitive/geometry2d/size.h"


namespace nano
{

namespace user
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

      _synchronous_lock synchronouslock(this->synchronization());

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






enum_display_type g_edisplaytype = e_display_type_none;


enum_display_type get_display_type()
{

   return g_edisplaytype;

}


void initialize_display_type(enum_display_type edisplaytype)
{

   g_edisplaytype = edisplaytype;

}





} // namespace user


} // namespace nano



