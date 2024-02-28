// Created by camilo on 2022-10-15 03:50 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/file/binary_stream.h"


// template < typename FILE >
binary_stream & operator <<(::binary_stream & stream, const ::networking_bsd::address & address)
{

   stream.write(&address.u.m_sa, sizeof(address.u.m_sa));
   stream << address.m_iLen;

   return stream;

}


// template < typename FILE >
binary_stream & operator >>(::binary_stream & stream, ::networking_bsd::address & address)
{

   stream.read(&address.u.m_sa, sizeof(address.u.m_sa));
   stream >> address.m_iLen;

   return stream;

}



// template < typename FILE >
binary_stream & operator <<(::binary_stream & stream, const networking::dns_cache_item & item)
{

   string strAddress;

   strAddress = as_string(item.m_ipaddr);

   stream << strAddress;
   stream << item.m_timeLastChecked;
   stream << item.m_bOk;
   stream << item.m_bTimeout;

   return stream;

}


// template < typename FILE >
binary_stream & operator >>(::binary_stream & stream, networking::dns_cache_item &item)
{

   string strAddress;

   stream >> strAddress;

   ::from_string(item.m_ipaddr, strAddress);

   stream >> item.m_timeLastChecked;
   stream >> item.m_bOk;
   stream >> item.m_bTimeout;

   return stream;

}



// template < typename FILE >
binary_stream & operator >>(::binary_stream & stream, const networking::reverse_cache_item & item)
{

   stream << item.m_strIpAddress;
   stream << item.m_strReverse;
   stream << item.m_timeLastChecked;
   stream << item.m_bOk;
   stream << item.m_bTimeout;
   stream << item.m_bProcessing;

   return stream;

}


// template < typename FILE >
binary_stream & operator >>(::binary_stream & stream, networking::reverse_cache_item & item)
{

   stream >> item.m_strIpAddress;
   stream >> item.m_strReverse;
   stream >> item.m_timeLastChecked;
   stream >> item.m_bOk;
   stream >> item.m_bTimeout;
   stream >> item.m_bProcessing;

   return stream;

}



// template < typename FILE >
inline binary_stream & operator <<(binary_stream & s, const ::in6_addr & addr)
{

   s.write(&addr, sizeof(addr));

   return s;

}


// template < typename FILE >
inline binary_stream & operator >>(binary_stream & s, ::in6_addr & addr)
{

   s.read(&addr, sizeof(addr));

   return s;

}


// template < typename FILE >
inline binary_stream & operator <<(binary_stream & s, const ::in_addr & addr)
{

   s.write(&addr, sizeof(addr));

   return s;

}


// template < typename FILE >
inline binary_stream & operator >>(binary_stream & s, ::in_addr & addr)
{

   s.read(&addr, sizeof(addr));

   return s;

}



