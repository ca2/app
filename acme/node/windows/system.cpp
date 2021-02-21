//
// Created by camilo on 05/12/2020. <3tbs!!
//
#include "framework.h"
#include "acme/operating_system.h"


namespace acme
{


   ::e_status system::start()
   {

      auto estatus = on_start();

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   ::e_status system::on_start()
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


   ::file::path system::get_memory_map_base_folder_path() const
   {
      
      auto path = get_known_folder(FOLDERID_RoamingAppData);

      path /= "ca2/memory_map";

      return path;

   }


} // namespace acme



