// First compilation from other files by camilo on 2022-10-07 23:30 <3ThomasBorregaardSorensen!!
#pragma once


inline binary_stream & operator << (binary_stream & s, const ::color::HLS & hls)
{

   s << hls.m_dH;
   s << hls.m_dL;
   s << hls.m_dS;

   return s;

}


inline binary_stream & operator >> (binary_stream & s, ::color::HLS & hls)
{

   s >> hls.m_dH;
   s >> hls.m_dL;
   s >> hls.m_dS;

   return s;

}



