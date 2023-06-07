// From file/binary_stream < FILE >.h by camilo on 2022-10-15 00:07 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/primitive/collection/_array_binary_stream.h"


template < typename FILE >
inline binary_stream < FILE > & operator <<(binary_stream < FILE > & s, const ::filehandler::item & item)
{

   s << (::i32)item.m_etopictype;
   s << item.m_strTopic;
   s << item.m_straHandlerLibrary;
   s << item.m_straMenuLibrary;
   s << item.m_straApp;
   return s;

}


template < typename FILE >
inline binary_stream < FILE > & operator >>(binary_stream < FILE > & s, ::filehandler::item & item)
{

   s >> (int &)item.m_etopictype;
   s >> item.m_strTopic;
   s >> item.m_straHandlerLibrary;
   s >> item.m_straMenuLibrary;
   s >> item.m_straApp;

   return s;

}



