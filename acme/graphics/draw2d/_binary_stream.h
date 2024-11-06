// First compilation from other files by camilo on 2022-10-07 23:30 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/file/binary_stream.h"


// template < typename FILE >
inline binary_stream & operator << (binary_stream & s, const ::color::HLS & hls)
{

   s << hls.m_dH;
   s << hls.m_dL;
   s << hls.m_dS;

   return s;

}


// template < typename FILE >
inline binary_stream & operator >> (binary_stream & s, ::color::HLS & hls)
{

   s >> hls.m_dH;
   s >> hls.m_dL;
   s >> hls.m_dS;

   return s;

}


// template < typename FILE >
inline binary_stream & operator << (binary_stream & s, const ::color::color & color)
{

   s << color.m_uchRed;
   s << color.m_uchGreen;
   s << color.m_uchBlue;
   s << color.m_uchOpacity;

   return s;

}


// template < typename FILE >
inline binary_stream & operator >> (binary_stream & s, ::color::color & color)
{

   s >> color.m_uchRed;
   s >> color.m_uchGreen;
   s >> color.m_uchBlue;
   s >> color.m_uchOpacity;

   return s;

}



