//
// Created by camilo on 2026-07-02 12:46 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "acme/prototype/collection/property_set.h"
#include "acme/filesystem/file/binary_stream.h"


CLASS_DECL_ACME binary_stream & operator <<(binary_stream & stream, const ::property_set & propertyset)
{

   return stream << (const property_holder_array_base & ) propertyset;

}


CLASS_DECL_ACME binary_stream & operator >>(binary_stream & stream, ::property_set & propertyset)
{

   return stream >> (property_holder_array_base &) propertyset;

}


CLASS_DECL_ACME binary_stream & operator <<(binary_stream & stream, const property_holder_array_base & a)
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


CLASS_DECL_ACME binary_stream & operator >>(binary_stream & stream, property_holder_array_base & a)
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

         a[i] = new property();

         stream >> *a[i];

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



