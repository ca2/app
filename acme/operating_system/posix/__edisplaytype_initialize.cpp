//
// Created by camilo on 2024-11-13 14:31 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "acme/constant/windowing2.h"

namespace windowing
{


   enum_display_type g_edisplaytype = e_display_type_none;


   enum_display_type get_edisplaytype()
   {

      return g_edisplaytype;

   }


   void initialize_edisplaytype(enum_display_type edisplaytype)
   {

      g_edisplaytype = edisplaytype;

   }


} // namespace windowing



