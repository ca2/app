//
// Created by camilo on 11/04-April/2022. 22:34 <3ThomasBorregaardSorensen!!
//
#include "framework.h"

#include <sys/utsname.h>

#if defined(FREEBSD) || defined(OPENBSD)
#include <strings.h>
#include <stdio.h>
#endif

namespace nano
{
   namespace user
   {
      ::user::enum_desktop g_edesktop = ::user::e_desktop_none;


      ::user::enum_desktop calculate_edesktop()
      {

         const char * pszDesktop = getenv("XDG_CURRENT_DESKTOP");

         printf("XDG_CURRENT_DESKTOP %s\n", pszDesktop);

         string strDesktop(pszDesktop);

         if(strDesktop.case_insensitive_order("kde") == 0)
         {

            printf("calculate_edesktop e_desktop_kde\n");

            return ::user::e_desktop_kde;

         }
         else if(strDesktop.case_insensitive_order("gnome") == 0)
         {

            printf("calculate_edesktop e_desktop_gnome\n");

            return ::user::e_desktop_gnome;

         }
         else if(strDesktop.case_insensitive_order("lxde") == 0)
         {

            printf("calculate_edesktop e_desktop_lxde\n");

            return ::user::e_desktop_lxde;

         }
         else if(strDesktop.case_insensitive_order("unity") == 0)
         {

            printf("calculate_edesktop e_desktop_unity_gnome\n");

            return ::user::e_desktop_unity_gnome;

         }

         // // utsname name;

         // // memory_set(&name, 0, sizeof(utsname));

         // // uname(&name);

         // if(pszDesktop != nullptr)
         // {

         //    if(strcasecmp(pszDesktop, "Unity") == 0)
         //    {

         //       return ::user::e_desktop_unity_gnome;

         //    }

         // }

         else if(is_directory("/etc/xdg/lubuntu"))
         {

            printf("calculate_edesktop e_desktop_lxde\n");

            return ::user::e_desktop_lxde;

         }
         else if(file_exists("/usr/bin/xfconf-query"))
         {

            printf("calculate_edesktop e_desktop_xfce\n");

            return ::user::e_desktop_xfce;

         }
         else if(file_exists("/usr/bin/mate-about"))
         {

            printf("calculate_edesktop e_desktop_mate\n");

            return ::user::e_desktop_mate;

         }
         else if(file_exists("/usr/bin/unity"))
         {

            printf("calculate_edesktop e_desktop_unity_gnome\n");

            return ::user::e_desktop_unity_gnome;

         }
         else if(strcasecmp(pszDesktop, "ubuntu:gnome") == 0)
         {

            printf("calculate_edesktop e_desktop_ubuntu_gnome\n");

            return ::user::e_desktop_ubuntu_gnome;

         }
         else if(strcasecmp(pszDesktop, "gnome") == 0)
         {

            printf("calculate_edesktop e_desktop_gnome\n");

            return ::user::e_desktop_gnome;

         }
         else
         {

            printf("calculate_edesktop e_desktop_gnome\n");

            return ::user::e_desktop_gnome;

         }

      }



      ::user::enum_desktop get_edesktop()
      {

         if (g_edesktop == ::user::e_desktop_none)
         {

            g_edesktop = calculate_edesktop();

         }

         return g_edesktop;

      }
   } // namespace user
} // namespace nano

