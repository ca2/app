// From file/binary_stream.h by camilo on 2022-10-14 23:46 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/file/binary_stream.h"


template < primitive_particle_array POINTER_ARRAY >
inline binary_stream & operator <<(binary_stream & stream, const POINTER_ARRAY & a)
{

   ::collection::count c = a.get_count();

   stream << c;

   for (auto & p : a)
   {

      stream.write_particle(p.m_p);

      if (stream.nok())
      {

         break;

      }

   }

   return stream;

}


template < primitive_particle_array POINTER_ARRAY >
inline binary_stream & operator >>(binary_stream & stream, POINTER_ARRAY & a)
{

   ::collection::count c;

   stream >> c;

   if (stream.nok())
   {

      return stream;

   }

   a.set_size(c);

   ::collection::index i = 0;

   try
   {

      for (; i < c && stream.has_ok_flag(); i++)
      {

         a[i] = stream.read_particle();

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


template < primitive_object_array ARRAY >
inline binary_stream & operator <<(binary_stream & stream, const ARRAY & a)
{

   ::collection::count c = a.get_count();
   
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


template < primitive_object_array ARRAY >
inline binary_stream & operator >>(binary_stream & stream, ARRAY & a)
{

   ::collection::count c;
   
   stream >> c;
   
   if (stream.nok() || c <= 0)
   {

      return stream;

   }
   
   a.set_size(c);

   ::collection::index i = 0;

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


template < primitive_raw_pointer_array ARRAY >
inline binary_stream & operator <<(binary_stream & stream, const ARRAY & a)
{

   ::collection::count c = a.get_count();
   
   stream << c;

   for (auto & p : a)
   {
      
      stream << *p;

      if (stream.nok())
      {

         break;

      }

   }

   return stream;

}


template < primitive_raw_pointer_array ARRAY >
inline binary_stream & operator >>(binary_stream & stream, ARRAY & a)
{

   ::collection::count c;
   
   stream >> c;

   if (stream.nok())
   {

      return stream;

   }

   a.set_size(c);

   ::collection::index i = 0;

   try
   {

      for (; i < c && stream.has_ok_flag(); i++)
      {
         
         auto p = new typename ARRAY::BASE_TYPE();
         
         a[i] = p;

         stream >> *p;

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


template < primitive_raw_type_array ARRAY >
inline binary_stream & operator <<(binary_stream & stream, const ARRAY & a)
{

   ::collection::count c = a.get_count();

   stream << c;

   stream.write({ a.get_data(), sizeof(typename ARRAY::BASE_TYPE) * c});

   return stream;

}

template < primitive_raw_type_array ARRAY >
inline binary_stream & operator >>(binary_stream & stream, ARRAY & a)
{
   
   ::collection::count c;
   
   stream >> c;
   
   if (stream.nok())
   {
      
      return stream;
      
   }
   
   a.set_size(c);
   
   auto iRead = stream.m_pfile->read({ a.get_data(), sizeof(typename ARRAY::BASE_TYPE) * c });
   
   if (stream.nok() || iRead < (memsize)(sizeof(typename ARRAY::BASE_TYPE) * c))
   {
      
      a.set_size(iRead / sizeof(typename ARRAY::BASE_TYPE));
      
   }
   
   return stream;
   
}


inline binary_stream & operator <<(binary_stream & stream, const ::property_set & propertyset)
{

   return stream << (const property_ptra & ) propertyset;

}


inline binary_stream & operator >>(binary_stream & stream, ::property_set & propertyset)
{

   return stream >> (property_ptra &) propertyset;

}




inline binary_stream & operator <<(binary_stream & stream, const ::property * pproperty)
{

   return stream << *pproperty;

}


inline binary_stream & operator >>(binary_stream & stream, ::property * pproperty)
{

   return stream >> *pproperty;

}




