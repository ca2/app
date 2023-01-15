// From file/binary_stream < FILE >.h by camilo on 2022-10-14 23:46 <3ThomasBorregaardSørensen!!
#pragma once


template < typename FILE, class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = allocator::nodef < TYPE >, ::enum_type m_etypeContainer >
inline binary_stream < FILE > & operator <<(binary_stream < FILE > & stream, const ::array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & a)
{

   ::count c = a.get_count();
   
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


template < typename FILE, class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = allocator::nodef < TYPE >, ::enum_type m_etypeContainer >
inline binary_stream < FILE > & operator >>(binary_stream < FILE > & stream, ::array_base < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & a)
{

   ::count c;
   
   stream >> c;

   if (stream.nok())
   {

      return stream;

   }

   a.set_size(c);

   ::index i = 0;

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


template < typename FILE, class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = allocator::nodef < TYPE >, ::enum_type m_etypeContainer >
inline binary_stream < FILE > & operator <<(binary_stream < FILE > & stream, const ::raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & a)
{

   ::count c = a.get_count();

   stream << c;

   stream.write(a.get_data(), sizeof(TYPE) * c);

   return stream;

}


template < typename FILE, class TYPE, class ARG_TYPE = const TYPE &, class ALLOCATOR = allocator::nodef < TYPE >, ::enum_type m_etypeContainer >
inline binary_stream < FILE > & operator >>(binary_stream < FILE > & stream, ::raw_array < TYPE, ARG_TYPE, ALLOCATOR, m_etypeContainer > & a)
{

   ::count c;

   stream >> c;

   if (stream.nok())
   {

      return stream;

   }

   a.set_size(c);

   auto iRead = stream.m_pfile->read(a.get_data(), sizeof(TYPE) * c);

   if (stream.nok() || iRead < (memsize)(sizeof(TYPE) * c))
   {

      a.set_size(iRead / sizeof(TYPE));

   }

   return stream;

}



