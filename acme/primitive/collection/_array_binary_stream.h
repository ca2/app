// From file/binary_stream.h by camilo on 2022-10-14 23:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/file/binary_stream.h"


template < class ITEM >
inline binary_stream & operator <<(binary_stream & stream, const ::pointer_array < ITEM > & itema)
{

   ::raw::count c = itema.get_count();

   stream << c;

   for (auto & pitem : itema)
   {

      stream.write_particle(pitem);

      if (stream.nok())
      {

         break;

      }

   }

   return stream;

}


template < class ITEM >
inline binary_stream & operator >>(binary_stream & stream, ::pointer_array < ITEM > & itema)
{

   ::raw::count c;

   stream >> c;

   if (stream.nok())
   {

      return stream;

   }

   itema.set_size(c);

   ::raw::index i = 0;

   try
   {

      for (; i < c && stream.has_ok_flag(); i++)
      {

         itema[i] = stream.read_particle();

      }

   }
   catch (...)
   {

      stream.set_nok();

   }

   if (stream.nok())
   {

      itema.set_size(i);

   }

   return stream;

}


template < class TYPE, class ARG_TYPE = const TYPE &, class TYPED = ::typed::nodef < TYPE >, class MEMORY = ::heap::typed_memory < TYPE, ::heap::e_memory_array >, ::enum_type t_etypeContainer = e_type_element >
inline binary_stream & operator <<(binary_stream & stream, const ::array_base_quantum < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & a)
{

   ::raw::count c = a.get_count();
   
   stream << c;

   for (auto & element : a)
   {
      stream << element;

      if (stream.nok())
      {

         break;

      }

   }

   return stream;

}


template < primitive_array ARRAY >
inline binary_stream & operator >>(binary_stream & stream, ARRAY & a)
{

   ::raw::count c;
   
   stream >> c;

   if (stream.nok())
   {

      return stream;

   }

   a.set_size(c);

   ::raw::index i = 0;

   try
   {

      for (; i < c && stream.has_ok_flag(); i++)
      {

         stream >> a[i];

      }

   }
   catch (...)
   {

      stream.set_nok();

   }

   if (stream.nok())
   {

      a.set_size(i);

   }

   return stream;

}


template < class TYPE, class ARG_TYPE = const TYPE &, class TYPED = ::typed::nodef < TYPE >, class MEMORY = ::heap::typed_memory < TYPE, ::heap::e_memory_array >, ::enum_type t_etypeContainer = e_type_element >
inline binary_stream & operator <<(binary_stream & stream, const ::raw_array_quantum < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & a)
{

   ::raw::count c = a.get_count();

   stream << c;

   stream.write({ a.get_data(), sizeof(TYPE) * c});

   return stream;

}


template < class TYPE, class ARG_TYPE = const TYPE &, class TYPED = ::typed::nodef < TYPE >, class MEMORY = ::heap::typed_memory < TYPE, ::heap::e_memory_array >, ::enum_type t_etypeContainer = e_type_element >
inline binary_stream & operator >>(binary_stream & stream, ::raw_array_quantum < TYPE, ARG_TYPE, TYPED, MEMORY, t_etypeContainer > & a)
{

   ::raw::count c;

   stream >> c;

   if (stream.nok())
   {

      return stream;

   }

   a.set_size(c);

   auto iRead = stream.m_pfile->read({ a.get_data(), sizeof(TYPE) * c });

   if (stream.nok() || iRead < (memsize)(sizeof(TYPE) * c))
   {

      a.set_size(iRead / sizeof(TYPE));

   }

   return stream;

}


inline binary_stream & operator <<(binary_stream & stream, const ::property_set & propertyset)
{

   return stream << propertyset.m_propertyptra;

}


inline binary_stream & operator >>(binary_stream & stream, ::property_set & propertyset)
{

   return stream >> propertyset.m_propertyptra;

}




inline binary_stream & operator <<(binary_stream & stream, const ::property * pproperty)
{

   return stream << *pproperty;

}


inline binary_stream & operator >>(binary_stream & stream, ::property * pproperty)
{

   return stream >> *pproperty;

}




