// First compilation from other files by camilo on 2022-10-07 23:30 <3ThomasBorregaardSorensen!!
#pragma once


template < typename FILE >
inline binary_stream < FILE > & operator << (binary_stream < FILE > & s, const ::color::HLS & hls)
{

   s << hls.m_dH;
   s << hls.m_dL;
   s << hls.m_dS;

   return s;

}


template < typename FILE >
inline binary_stream < FILE > & operator >> (binary_stream < FILE > & s, ::color::HLS & hls)
{

   s >> hls.m_dH;
   s >> hls.m_dL;
   s >> hls.m_dS;

   return s;

}



