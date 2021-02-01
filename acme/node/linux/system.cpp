//
// Created by camilo on 02/12/2020  <3tbs!!
// (as acme/os/linux/application_system_run.cpp)
// Created by Camilo 2020-12-29 16:25 BRT <3TBS, Mummi and bilbo!!
// (as acme/node/linux/system.cpp)
#include "framework.h"
//!!!#include "acme/os/x11/_x11.h"


namespace acme
{


   ::e_status system::os_application_system_run()
   {

      return ::success;

   }


   void system::os_construct()
   {

      auto lines = file_as_lines("/etc/os-release");

      ::string strId;

      if(lines.find_first_begins_eat_ci(strId, "id="))
      {

         strId.make_lower();

         if (strId == "ubuntu")
         {

            m_elinuxdistribution = e_linux_distribution_ubuntu;

         }
         else if (strId == "manjaro")
         {

            m_elinuxdistribution = e_linux_distribution_manjaro;

         }

      }

      if(m_elinuxdistribution <= 0)
      {

         output_debug_string("WARNING: Unknown linux distribution with id \"" + strId + "\".");

      }

   }


   enum_operating_system system::get_operating_system() const
   {

       return e_operating_system_linux;

   }

//
//   ::e_status system::defer_initialize_x11()
//   {
//
//      auto estatus = ::defer_initialize_x11();
//
//      return estatus;
//
//   }




   ::user::enum_desktop system::calc_edesktop()
   {

      const char * pszDesktop = getenv("XDG_CURRENT_DESKTOP");

      //utsname name;

      //memset(&name, 0, sizeof(utsname));

      //uname(&name);

      if(pszDesktop != nullptr)
      {

         if(strcasecmp(pszDesktop, "KDE") == 0)
         {

            return ::user::e_desktop_kde;

         }
         else if(strcasecmp(pszDesktop, "Unity") == 0)
         {

            return ::user::e_desktop_unity_gnome;

         }
         else if(strcasecmp(pszDesktop, "ubuntu:gnome") == 0)
         {

            return ::user::e_desktop_ubuntu_gnome;

         }

      }

      if(is_dir("/etc/xdg/lubuntu"))
      {

         return ::user::e_desktop_lxde;

      }
      else if(file_exists("/usr/bin/xfconf-query"))
      {

         return ::user::e_desktop_xfce;

      }
      else if(file_exists("/usr/bin/mate-about"))
      {

         return ::user::e_desktop_mate;

      }
      else if(file_exists("/usr/bin/unity"))
      {

         return ::user::e_desktop_unity_gnome;

      }

      return ::user::e_desktop_gnome;

   }


} // namespace acme



