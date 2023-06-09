// Created by camilo on 2022-10-15 04:09 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/file/binary_stream.h"
#include "axis/platform/geo_department.h"


template < typename FILE >
inline binary_stream < FILE > & operator <<(binary_stream < FILE > & stream, const class ::string_timeout & t)
{

   stream << t.m_str;
   stream << t.m_time;

   return stream;

}


template < typename FILE >
inline binary_stream < FILE > & operator >>(binary_stream < FILE > & stream, class ::string_timeout & t)
{

   stream >> t.m_str;
   stream >> t.m_time;

   return stream;

}




