//
// Created by camilo on 8/16/22.  <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "aura/windowing/desktop_environment.h"


namespace windowing
{


   desktop_environment::desktop_environment()
   {

      m_bUnhook = false;

   }


   desktop_environment::~desktop_environment()
   {



   }


   void desktop_environment::get_monitor_rectangle(::index iMonitor, ::rectangle_i32 * prectangle)
   {


   }


   void desktop_environment::get_workspace_rectangle(::index iMonitor, ::rectangle_i32 * prectangle)
   {



   }





   void desktop_environment::windowing_post(const ::procedure & procedure)
   {


   }


   bool desktop_environment::message_loop_step()
   {

      return true;

   }


} // namespace windowing




