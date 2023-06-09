// From file/binary_stream < FILE >.h by camilo on 2022-10-14 23:58 <3ThomasBorregaardSorensen!!
#pragma once




template < typename FILE, typename PAIR >
inline binary_stream < FILE > & operator <<(binary_stream < FILE > & stream, const pair_map < PAIR > & m)
{


   ::count c = m.get_count();

   stream << c;

   for (auto & pair : m)
   {

      stream << pair.element1();

      //if (s.fail())
        // break;

      stream << pair.element2();

      //if (s.fail())
        // break;

   }

   return stream;

}


template < typename FILE, typename PAIR >
inline binary_stream < FILE > & operator >>(binary_stream < FILE > & stream, pair_map < PAIR > & m)
{

   ::count c = 0;

   stream >> c;

   auto i = c;

   while (i > 0)
   {

      i--;

      typename pair_map < PAIR >::BASE_ITEM element1;
      //typename map < KEY, ARG_KEY, PAYLOAD, ARG_VALUE, PAIR >::BASE_VALUE element2;
      
      stream >> element1;

      if (stream.nok())
      {

         break;

      }
      
      stream >> m[element1];
      
      if (stream.nok())
      {

         m.erase_item(element1);

         break;

      }
      
      //m.set_at(element1, element2);

   }

   return stream;

}



