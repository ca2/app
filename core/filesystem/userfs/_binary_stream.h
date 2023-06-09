// from item.cpp by camilo on 2022-10-15 04:42 <3ThomasBorregaardSorensen!!
#pragma once


template < typename FILE >
binary_stream < FILE > &  operator <<(binary_stream < FILE > & s, const ::userfs::item & item)
{

   s << (::data::item &)item;
   s << (::file::item &)item;

   return s;

}


template < typename FILE >
binary_stream < FILE > & operator >>(binary_stream < FILE > & s, ::userfs::item & item)
{

   //::data::item::read(s);
   //::file::item::read(s);

   s >> (::data::item &) item;
   s >> (::file::item &)item;

   return s;

}



