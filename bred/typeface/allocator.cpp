// Created by camilo on 2026-01-06 21:11 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "allocator.h"


namespace typeface
{


   allocator::allocator() {}


   allocator ::~allocator() {}


   ::pointer<::typeface::typeface> allocator::create_typeface(const ::scoped_string &scopedstrName)
   {

      throw ::interface_only();

      return {};

   }


   ::pointer<::typeface::face> allocator::create_face(const ::scoped_string &scopedstrName)
   {

      throw ::interface_only();

      return {};

   }


} // namespace typeface



