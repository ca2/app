// Created by camilo on 2022-11-09 10:16 <3ThomasBorregaardSorensen!!
#pragma once


// template < typename FILE >
text_stream < FILE >& operator <<(text_stream < FILE >& stream, const ::property_set & set)
{

   stream << set.get_network_payload();

   return *this;

}



