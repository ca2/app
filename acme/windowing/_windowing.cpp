//
// Created by camilo on 2024-10-05 20:24 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "windowing.h"
#include "acme/constant/windowing2.h"


::string as_string(::windowing::enum_toolkit etoolkit)
{

   ::string str;

   switch (etoolkit)
   {
   case ::windowing::e_toolkit_none:     str = "(none)"; break;
   case ::windowing::e_toolkit_unknown:  str = "(unknown)"; break;
   case ::windowing::e_toolkit_win32:    str = "win32"; break;
   case ::windowing::e_toolkit_gtk3:     str = "gtk3"; break;
   case ::windowing::e_toolkit_gtk4:     str = "gtk4"; break;
   case ::windowing::e_toolkit_kde5:     str = "kde5"; break;
   case ::windowing::e_toolkit_kde6:     str = "kde6"; break;
   case ::windowing::e_toolkit_lxq2:     str = "lxq2"; break;
   case ::windowing::e_toolkit_lxq1:     str = "lxq1"; break;
   case ::windowing::e_toolkit_appkit:   str = "appkit"; break;
   case ::windowing::e_toolkit_uikit:    str = "uikit"; break;
   case ::windowing::e_toolkit_android:  str = "android"; break;
   case ::windowing::e_toolkit_universal_windows:  str = "universal_windows"; break;
   default:
   {
      throw "currently unknonw toolkit";
         break;

   }
   }


   return str;

}