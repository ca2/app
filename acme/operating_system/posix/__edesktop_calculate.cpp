//
// Created by camilo on 11/04-April/2022. 22:34 <3ThomasBorregaardSorensen!!
//
#include "framework.h"

#include <sys/utsname.h>

#if defined(__BSD__)
#include <stdio.h>
#include <strings.h>
#endif


namespace windowing
{


   ::windowing::enum_operating_ambient g_eoperatingambient = ::windowing::e_operating_ambient_none;


   ::windowing::enum_operating_ambient calculate_edesktop()
   {
      
#if defined(APPLE_IOS)
         
         printf_line("calculate_edesktop e_operating_ambient_ios");

         return ::windowing::e_operating_ambient_ios;

#elif defined(MACOS)
         
         printf_line("calculate_edesktop e_operating_ambient_macos");

         return ::windowing::e_operating_ambient_macos;
      
#else

      const char *pszDesktop = getenv("XDG_CURRENT_DESKTOP");

      printf_line("XDG_CURRENT_DESKTOP %s", pszDesktop);

      string strDesktop(pszDesktop);

      if (strDesktop.case_insensitive_order("kde") == 0)
      {

         printf_line("calculate_edesktop e_operating_ambient_kde");

         return ::windowing::e_operating_ambient_kde;
         
      }
      else if (strDesktop.case_insensitive_order("gnome") == 0)
      {

         printf_line("calculate_edesktop e_operating_ambient_gnome");

         return ::windowing::e_operating_ambient_gnome;
         
      }
      else if (strDesktop.case_insensitive_order("lxde") == 0)
      {

         printf_line("calculate_edesktop e_operating_ambient_lxde");

         return ::windowing::e_operating_ambient_lxde;
         
      }
      else if (strDesktop.case_insensitive_order("unity") == 0)
      {

         printf_line("calculate_edesktop e_operating_ambient_unity_gnome");

         return ::windowing::e_operating_ambient_unity;
         
      }

      // // utsname name;

      // // memory_set(&name, 0, sizeof(utsname));

      // // uname(&name);

      // if(pszDesktop != nullptr)
      // {

      //    if(strcasecmp(pszDesktop, "Unity") == 0)
      //    {

      //       return ::windowing::e_operating_ambient_unity_gnome;

      //    }

      // }

      else if (is_directory("/etc/xdg/lubuntu"))
      {

         printf_line("calculate_edesktop e_operating_ambient_lxde");

         return ::windowing::e_operating_ambient_lxde;
         
      }
      else if (file_exists("/usr/bin/xfconf-query") || file_exists("/usr/pkg/bin/xfconf-query"))
      {

         printf_line("calculate_edesktop e_operating_ambient_xfce");

         return ::windowing::e_operating_ambient_xfce;
         
      }
      else if (file_exists("/usr/bin/cinnamon"))
      {

         printf_line("calculate_edesktop e_operating_ambient_cinnamon");

         return ::windowing::e_operating_ambient_cinnamon;
         
      }
      else if (file_exists("/usr/bin/mate-about"))
      {

         printf_line("calculate_edesktop e_operating_ambient_mate");

         return ::windowing::e_operating_ambient_mate;
         
      }
      else if (file_exists("/usr/bin/unity"))
      {

         printf_line("calculate_edesktop e_operating_ambient_unity_gnome");

         return ::windowing::e_operating_ambient_unity;
         
      }
      else if (strDesktop.case_insensitive_order("ubuntu:gnome") == 0)
      {

         printf_line("calculate_edesktop e_operating_ambient_ubuntu_gnome");

         return ::windowing::e_operating_ambient_unity;
         
      }
      else if (strDesktop.case_insensitive_order("gnome") == 0)
      {

         printf_line("calculate_edesktop e_operating_ambient_gnome");

         return ::windowing::e_operating_ambient_gnome;
         
      }
      else
      {
         
         printf_line("calculate_edesktop e_operating_ambient_gnome (1)");

         return ::windowing::e_operating_ambient_gnome;
         
      }
      
#endif
      
   }


   ::windowing::enum_operating_ambient get_eoperating_ambient()
   {

      if (g_eoperatingambient == ::windowing::e_operating_ambient_none)
      {

         g_eoperatingambient = calculate_edesktop();
      }

      return g_eoperatingambient;
   }
   
   
} // namespace windowing
