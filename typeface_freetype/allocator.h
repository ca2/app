// Created by camilo on 2026-01-06 22:21 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/typeface/allocator.h"


namespace typeface_freetype
{


   class CLASS_DECL_TYPEFACE_FREETYPE allocator : virtual public ::typeface::allocator
   {
   public:


      allocator();
      ~allocator() override;


      ::pointer<::typeface::typeface> create_typeface(const ::scoped_string &scopedstrName) override;

      ::pointer<::typeface::face> create_face(const ::scoped_string &scopedstrName) override;


   };


} // namespace typeface_freetype
