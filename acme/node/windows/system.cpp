//
// Created by camilo on 05/12/2020. <3tbs!!
//
#include "framework.h"
#include "acme/operating_system.h"


namespace acme
{


   ::e_status system::end()
   {

      auto estatus = on_end();

      if (!estatus)
      {

         return estatus;

      }

      estatus = inline_term();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::apex::application* system::get_main_application()
   {

      return nullptr;

   }


   void system::system_construct(int argc, char** argv, char** envp)
   {


   }


   void system::system_construct(int argc, wchar_t** argv, wchar_t** envp)
   {


   }


   ::e_status system::inline_init()
   {

      auto estatus = process_init();

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

   }


   ::e_status system::inline_term()
   {

      return ::success;

   }

   
   ::e_status system::on_end()
   {

      return ::success;

   }


   void system::os_construct()
   {


   }


   ::enum_operating_system system::get_operating_system() const
   {

      return ::e_operating_system_windows;

   }


   ::user::enum_desktop system::calc_edesktop()
   {

      return ::user::e_desktop_windows;

   }


} // namespace acme



