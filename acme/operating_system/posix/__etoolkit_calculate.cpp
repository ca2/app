//
// Created by camilo on 11/04-April/2022. 22:34 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "acme/constant/windowing2.h"
#include <sys/utsname.h>

#if defined(__BSD__)
#include <stdio.h>
#include <strings.h>
#endif


namespace windowing
{


   ::windowing::enum_toolkit g_etoolkit = ::windowing::e_toolkit_none;


   ::windowing::enum_toolkit calculate_etoolkit()
   {
#if defined(__ANDROID__)
      return ::windowing::e_toolkit_android;
#elif defined(MACOS)
      return ::windowing::e_toolkit_appkit;
#elif defined(APPLE_IOS)
      return ::windowing::e_toolkit_uikit;
#elif defined(WINDOWS_DESKTOP)
      return ::windowing::e_toolkit_win32;
#elif defined(HAS_KDE5)
      return ::windowing::e_toolkit_kde5;
#elif defined(HAS_KDE6)
      return ::windowing::e_toolkit_kde6;
#elif defined(HAS_GTK4)
      return ::windowing::e_toolkit_gtk4;
#elif defined(HAS_GTK3)
      return ::windowing::e_toolkit_gtk3;
#elif defined(HAS_LXQ2)
      return ::windowing::e_toolkit_lxq2;
#elif defined(HAS_LXQ1)
      return ::windowing::e_toolkit_lxq1;
#else
      return ::windowing::e_toolkit_unknown;
#endif

   }


   ::windowing::enum_toolkit get_etoolkit()
   {

      if (g_etoolkit == ::windowing::e_toolkit_none)
      {

         g_etoolkit = calculate_etoolkit();
         
      }

      return g_etoolkit;
      
   }
   
   
   /*::windowing::enum_toolkit get_edesktopenvironment()
   {
      
      if(g_edesktopenvironment == ::windowing::e_operating_ambient_environment_none)
      {
         
         g_edesktopenvironment = calculate_edesktopenvironment();
         
      }
      
      return g_edesktopenvironment;
      
   }*/


} // namespace windowing
