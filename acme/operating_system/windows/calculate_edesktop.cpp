//
// Created by camilo on 2024-10-20 00:03 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "acme/constant/windowing2.h"


namespace windowing
{


   ::windowing::enum_operating_ambient g_eoperatingambient = ::windowing::e_operating_ambient_none;


   ::windowing::enum_operating_ambient calculate_edesktop()
   {

      return ::windowing::e_operating_ambient_windows;

   }


   ::windowing::enum_operating_ambient get_eoperating_ambient()
   {

      if (g_eoperatingambient == ::windowing::e_operating_ambient_none)
      {

         g_eoperatingambient = calculate_edesktop();

      }

      return g_eoperatingambient;

   }


} // namespace user


