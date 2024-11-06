// First compilation from other files by camilo on 2022-10-07 23:30 <3ThomasBorregaardSorensen!!
#pragma once


inline write_text_stream & operator << (write_text_stream & s, const ::color::color & color)
{

   if (s.fmtflags() & ::file::hex)
   {

      s.append_format("rgb(%3x,%3x,%3x,%0.2f)",
         color.byte_red(),
         color.byte_green(),
         color.byte_blue(),
         color.f32_opacity());

   }
   else
   {

      s.append_format("rgb(%3d,%3d,%3d,%0.2f)",
                      color.byte_red(),
                      color.byte_green(),
                      color.byte_blue(),
                      color.f32_opacity());

   }

   return s;

}






