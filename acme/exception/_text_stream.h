// Created by camilo on 2022-11-09 10:41 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/file/text_stream.h"


template < typename FILE >
inline write_text_stream < FILE >& operator <<(write_text_stream < FILE >& stream, const ::exception& exception)
{

   stream << exception.get_message();

   return stream;

}



