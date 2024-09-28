//
// Created by camilo on 11/04-April/2022. 22:34 <3ThomasBorregaardSorensen!!
//
#include "framework.h"

#include <sys/utsname.h>

#if defined(__BSD__)
#include <strings.h>
#include <stdio.h>
#endif


namespace nano
{


   namespace user
   {


      ::user::enum_toolkit g_etoolkit = ::user::e_toolkit_none;


      ::user::enum_toolkit calculate_etoolkit()
      {

#if defined(WINDOWS_DESKTOP)
         return ::user::e_toolkit_win32;
#elif defined(HAS_KDE5)
         return ::user::e_toolkit_kde5;
#elif defined(HAS_KDE6)
         return ::user::e_toolkit_kde6;
#elif defined(HAS_GTK3)
         return ::user::e_toolkit_kde5;
#elif defined(HAS_GTK4)
         return ::user::e_toolkit_kde6;
#else
         return ::user::e_toolkit_unknown;
#endif

      }


      ::user::enum_toolkit get_etoolkit()
      {

         if (g_etoolkit == ::user::e_toolkit_none)
         {

            g_etoolkit = calculate_etoolkit();

         }

         return g_etoolkit;

      }


   } // namespace user


} // namespace nano



