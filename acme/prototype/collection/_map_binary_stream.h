// From file/binary_stream.h by camilo on 2022-10-14 23:58 <3ThomasBorregaardSorensen!!
#pragma once


template <  typename PAIR >
inline binary_stream & operator <<(binary_stream & stream, const pair_map_base < PAIR > & m)
{


   ::collection::count c = m.get_count();

   stream << c;

   for (auto & item : m)
   {

      stream << item.element1();

      //if (s.fail())
        // break;

      stream << item.element2();

      //if (s.fail())
        // break;

   }

   return stream;

}


template < typename PAIR >
inline binary_stream & operator >>(binary_stream & stream, pair_map_base < PAIR > & m)
{

   ::collection::count c = 0;

   stream >> c;

   auto i = c;

   while (i > 0)
   {

      i--;

      typename pair_map_base < PAIR >::KEY key;

      stream >> key;

      if (stream.nok())
      {

         break;

      }

      auto & payload = m[key];
      
      stream >> payload;
      
      if (stream.nok())
      {

         m.erase(key);

         break;

      }
      
      //m.set_at(element1, element2);

   }

   return stream;

}



