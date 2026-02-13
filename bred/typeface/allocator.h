// Created by camilo on 2026-01-06 21:11 <3ThomasBorregaardSørensen!!
#pragma once


namespace typeface
{


   class CLASS_DECL_BRED allocator : virtual public ::particle
   {
   public:


      allocator();
      ~allocator() override;


      virtual ::pointer<::typeface::typeface> create_typeface(const ::scoped_string &scopedstrName);

      virtual ::pointer<::typeface::face> create_face(const ::scoped_string &scopedstrName);

      
   };


} // namespace typeface
