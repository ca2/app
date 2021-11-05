#pragma once


#include "acme/filestream.h"
#include "collection.h"


template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR >
stream & operator << (stream & os, const ::property_map & a)
{
   ::file::map::write(os, a);
   return os;
}

template < class KEY, class ARG_KEY, class VALUE, class ARG_VALUE, class PAIR >
stream & operator >> (stream & is, property_map & a)
{
   ::file::map::read(is, a);
   return is;
}




