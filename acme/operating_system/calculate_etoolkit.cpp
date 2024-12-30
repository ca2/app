//
// Created by camilo on 11/04-April/2022. 22:34 <3ThomasBorregaardSorensen!!
//
#include "framework.h"


namespace windowing
{


   ::windowing::enum_toolkit g_etoolkit = ::windowing::e_toolkit_none;


   ::windowing::enum_toolkit calculate_etoolkit()
   {

#if defined(WINDOWS_DESKTOP)
      return ::windowing::e_toolkit_win32;
#elif defined(UNIVERSAL_WINDOWS)
      return ::windowing::e_toolkit_universal_windows;
#elif defined(HAS_KDE5)
      return ::windowing::e_toolkit_kde5;
#elif defined(HAS_KDE6)
      return ::windowing::e_toolkit_kde6;
#elif defined(HAS_GTK3)
      return ::windowing::e_toolkit_gtk3;
#elif defined(HAS_GTK4)
      return ::windowing::e_toolkit_gtk4;
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


} // namespace windowing



