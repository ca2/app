//
// Created by camilo on 31/01/2022.
//
#include "framework.h"
#include "acme/prototype/prototype/factory.h"

//
// void operating_system_initialize_nano_user(::factory::factory * pfactory);
//
//
// bool g_bNanoUserInitialize = false;
//
//
// CLASS_DECL_ACME void initialize_nano_user(::factory::factory * pfactory)
// {
//
//    if(g_bNanoUserInitialize)
//    {
//
//       return;
//
//    }
//
//    operating_system_initialize_nano_user(pfactory);
//
//    g_bNanoUserInitialize = true;
//
// }


::string as_string(::user::enum_toolkit etoolkit)
{

   ::string str;

   switch(etoolkit)
   {
   case ::user::e_toolkit_none:     str = "(none)"    ; break;
   case ::user::e_toolkit_unknown:  str = "(unknown)" ; break;
   case ::user::e_toolkit_win32:    str = "win32"     ; break;
   case ::user::e_toolkit_gtk3:     str = "gtk3"      ; break;
   case ::user::e_toolkit_gtk4:     str = "gtk4"      ; break;
   case ::user::e_toolkit_kde5:     str = "kde5"      ; break;
   case ::user::e_toolkit_kde6:     str = "kde6"      ; break;
   case ::user::e_toolkit_appkit:   str = "appkit"    ; break;
   case ::user::e_toolkit_uikit:    str = "uikit"     ; break;
   case ::user::e_toolkit_android:  str = "android"   ; break;
      default:break;
   }


   return str;

}