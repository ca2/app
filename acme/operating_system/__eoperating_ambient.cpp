// Created by camilo on 2024-11-16 15:49 <3ThomasBorregaardSorensen!!
#include "framework.h"


namespace windowing
{


   ::string get_eoperating_ambient_name()
   {
      
      auto eoperatingambient = get_eoperating_ambient();
      
      switch(eoperatingambient)
      {
      case e_operating_ambient_xfce:
         return "xfce";
      case e_operating_ambient_ios:
         return "ios";
      case e_operating_ambient_windows:
         return "windows";
      case e_operating_ambient_unity:
         return "gtk_based";
      default:
         throw todo;
      };
      
      return {};

   }


} // namespace windowing




