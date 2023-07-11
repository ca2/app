// Created by camilo on 2023-06-28 16:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/primitive/targeted_unit.h"


namespace write_text
{

   struct font_size_allowed_units
   {

      inline static enum_unit* allowed_units()
      {

         static enum_unit eunitaFontSizeAllowed[] = { e_unit_pixel, e_unit_point, e_unit_rate, e_unit_none };

         return eunitaFontSizeAllowed;

      }

   };


   using font_size = ::targeted_unit < enum_unit, font_size_allowed_units >;


} // namespace write_text



