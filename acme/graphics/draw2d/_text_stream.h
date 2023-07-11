// First compilation from other files by camilo on 2022-10-07 23:30 <3ThomasBorregaardSorensen!!
#pragma once


inline write_text_stream & operator << (write_text_stream & s, const ::color::color & color)
{

   if (s.fmtflags() & ::file::hex)
   {

      s.append_format("rgb(%3d,%3d,%3d,%0.2f)", 
         color.u8_red(),
         color.u8_green(),
         color.u8_blue(),
         color.f32_opacity());

   }
   else
   {

      s << color.m_u8Red;
      s << color.m_u8Green;
      s << color.m_u8Blue;
      s << color.m_u8Opacity;

   }

   return s;

}






