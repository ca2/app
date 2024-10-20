//
// Created by camilo on 2024-10-20 00:03 <3ThomasBorregaardSorensen!!
//
#include "framework.h"


namespace windowing
{


   ::windowing::enum_desktop g_edesktop = ::windowing::e_desktop_none;


   ::windowing::enum_desktop calculate_edesktop()
   {

      return ::windowing::e_desktop_windows;

   }


   ::windowing::enum_desktop get_edesktop()
   {

      if (g_edesktop == ::windowing::e_desktop_none)
      {

         g_edesktop = calculate_edesktop();

      }

      return g_edesktop;

   }


} // namespace user


