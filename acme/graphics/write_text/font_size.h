// Created by camilo on 2023-06-28 16:46 <3ThomasBorregaardSorensen!!
#pragma once


namespace write_text
{


   inline constinit static enum_unit g_eunitaAllowFontSize[] = 
   {
      
      e_unit_pixel,
      e_unit_point,
      e_unit_rate,
      e_unit_none 

   };


   using font_size = ::targeted_unit < enum_unit, g_eunitaAllowFontSize >;


} // namespace write_text



