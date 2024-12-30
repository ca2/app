//
// From windows/calculate_edesktop.cpp by
//    camilo on 2024-12-29 10:04 <3ThomasBorregaardSorensen!!
//
#include "framework.h"


namespace windowing
{


   ::windowing::enum_operating_ambient g_eoperatingambient = ::windowing::e_operating_ambient_none;


   ::windowing::enum_operating_ambient calculate_edesktop()
   {

      return ::windowing::e_operating_ambient_universal_windows;

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


