// Created by camilo on 2022-10-15 04:09 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/file/binary_stream.h"
#include "axis/platform/geo_department.h"


// template < typename FILE >
inline binary_stream & operator <<(binary_stream & stream, const class ::string_timeout & t)
{

   stream << t.m_str;
   stream << t.m_time;

   return stream;

}


// template < typename FILE >
inline binary_stream & operator >>(binary_stream & stream, class ::string_timeout & t)
{

   stream >> t.m_str;
   stream >> t.m_time;

   return stream;

}




