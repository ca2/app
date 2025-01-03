// Created by camilo on 2024-11-16 15:49 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/windowing/_.h"


namespace windowing
{


   ::string get_eoperating_ambient_name()
   {
      
      auto eoperatingambient = get_eoperating_ambient();
      
      switch(eoperatingambient)
      {
      case e_operating_ambient_xfce:
         //return "xfce";
         return "gtk3";
      case e_operating_ambient_ios:
         return "ios";
      case e_operating_ambient_macos:
         return "macos";
      case e_operating_ambient_windows:
         return "windows";
      //case e_operating_ambient_unity:
        // return "gtk_based";
         case e_operating_ambient_unity:
      case e_operating_ambient_gnome:
#ifdef HAS_GTK4
         return "gtk4";
#else
         return "gtk3";
#endif
      case e_operating_ambient_universal_windows:
         return "universal_windows";
      default:
         throw todo;
      };
      
      return {};

   }


} // namespace windowing




