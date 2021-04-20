//
// Created by camilo on 05/12/2020. <3tbs!!
//
#include "framework.h"
#include "acme/operating_system.h"


namespace acme
{


   ::e_status system::start()
   {

      //auto estatus = create_os_node();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //if (m_pnode)
      //{

      //   auto estatus = m_pnode->start();

      //}

      auto estatus = inline_init();

      if (!estatus)
      {

         return estatus;

      }

      estatus = on_start_system();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status system::end()
   {

      //auto estatus = create_os_node();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //if (m_pnode)
      //{

      //   auto estatus = m_pnode->start();

      //}

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


   void system::process_exit_status(::object* pobject, const ::e_status& estatus)
   {

      if (estatus == error_exit_system)
      {
      
         m_psystem->finish();
      
      }
      //   else if (estatus == error_exit_session)
      //   {
      //
      //      get_session()->finish();
      //
      //   }
      //   else if (estatus == error_exit_application)
      //   {
      //
      //      get_session()->finish();
      //
      //   }
      //   else if (estatus == error_exit_application)
      //   {
      //
      //      ::get_task()->finish();
      //
      //   }
      //

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

   
   ::e_status system::on_start_system()
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


   // ::file::path system::get_memory_map_base_folder_path() const
   // {
      
   //    auto path = get_known_folder(FOLDERID_RoamingAppData);

   //    path /= "ca2/memory_map";

   //    return path;

   // }


} // namespace acme



