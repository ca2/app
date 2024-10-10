//
// Created by camilo on 2024-10-05. 22:37 <3ThomasBorregaardSorensen!!
//
#include "framework.h"


namespace windowing
{


   ::windowing::enum_windowing g_ewindowing = ::windowing::e_windowing_none;


   ::windowing::enum_windowing calculate_ewindowing()
   {

#if defined(WINDOWS_DESKTOP)
      return ::windowing::e_windowing_win32;
#elif defined(HAS_KDE5)
      return ::windowing::e_windowing_kde5;
#elif defined(HAS_KDE6)
      return ::windowing::e_windowing_kde6;
#elif defined(HAS_GTK3)
      return ::windowing::e_windowing_gtk3;
#elif defined(HAS_GTK4)
      return ::windowing::e_windowing_gtk4;
#else
      return ::windowing::e_windowing_unknown;
#endif

   }


   ::windowing::enum_windowing get_ewindowing()
   {

      if (g_ewindowing == ::windowing::e_windowing_none)
      {

         g_ewindowing = calculate_ewindowing();

      }

      return g_ewindowing;

   }


} // namespace windowing
