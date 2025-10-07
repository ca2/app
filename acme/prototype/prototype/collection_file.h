#pragma once


#include "acme/filestream.h"
#include "collection.h"


template < class KEY, class ARG_KEY, class PAYLOAD, class ARG_VALUE, class PAIR >
stream & operator << (stream & os, const ::property_map & a)
{
   ::file::map_base::write(os, a);
   return os;
}

template < class KEY, class ARG_KEY, class PAYLOAD, class ARG_VALUE, class PAIR >
stream & operator >> (stream & is, property_map & a)
{
   ::file::map_base::read(is, a);
   return is;
}




