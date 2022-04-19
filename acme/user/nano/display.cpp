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


   void display::display_post(const ::procedure & function)
   {

      synchronous_lock synchronouslock(mutex());

      m_functionaPost.add(function);

      kick_idle();

   }


   void display::display_send(const ::procedure & function)
   {

//      if(m_bUnhook)
//      {
//
//
//
//      }

      /*auto estatus = */ __send_routine(this, &display::display_post, function.m_ppredicate);

      //if(!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }



   bool display::display_posted_routine_step()
   {

      synchronous_lock synchronouslock(mutex());

      if (m_functionaPost.has_element())
      {

         auto function = m_functionaPost.pick_first();

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




