//
// Created by camilo <3ThomasBorregaardSorensen!!
//
#include "framework.h"


CLASS_DECL_ACME bool is_docking(enum_display edisplay)
{

   return (edisplay & e_display_docking_mask) && edisplay > 0;

}


CLASS_DECL_ACME enum_display default_equivalence_sink(enum_display edisplay)
{

   if (edisplay <= 0)
   {

      return e_display_none;

   }

   if (edisplay < e_display_last_show)
   {

      return edisplay;

   }

   if (edisplay < e_display_default)
   {

      return e_display_normal;

   }

   if (edisplay >= e_display_default && edisplay < e_display_last_command)
   {

      return edisplay;

   }

   if (edisplay < e_display_left)
   {

      return e_display_default;

   }

   if (::is_docking(edisplay))
   {

      return edisplay;

   }

   return e_display_normal;

}



