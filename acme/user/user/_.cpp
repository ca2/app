//
// Created by camilo <3ThomasBorregaardSorensen!!
//
#include "framework.h"


CLASS_DECL_ACME bool is_docking(const ::e_display & edisplay)
{

   return (edisplay & e_display_docking_mask) && edisplay.m_cflag > 0;

}


CLASS_DECL_ACME ::e_display default_equivalence_sink(const ::e_display & edisplay)
{

   if (edisplay.m_cflag <= 0)
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



