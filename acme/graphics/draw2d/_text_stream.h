// First compilation from other files by camilo on 2022-10-07 23:30 <3ThomasBorregaardSorensen!!
#pragma once


template < typename FILE >
inline write_text_stream < FILE > & operator << (write_text_stream < FILE > & s, const ::color::color & color)
{

   s << color.m_u8Red;
   s << color.m_u8Green;
   s << color.m_u8Blue;
   s << color.m_u8Opacity;

   return s;

}






