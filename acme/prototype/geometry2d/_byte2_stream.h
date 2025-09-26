//
// Created by camilo on 2025-08-31 17:22 <3ThomasBorregaardSorensen
//
#pragma once

#include "acme/filesystem/file/byte2_stream.h"

template < primitive_number NUMBER >
inline byte2_stream &  operator >> (byte2_stream & stream, size_type < NUMBER > &size)
{

   stream >> size.cx();
   stream >> size.cy();

   return stream;

}


template < primitive_number NUMBER >
inline byte2_stream &  operator << (byte2_stream & stream, const size_type < NUMBER > &size)
{

   stream << size.cx();
   stream << size.cy();

   return stream;

}



