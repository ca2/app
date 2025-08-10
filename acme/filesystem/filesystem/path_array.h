// Created by camilo on 2022-03-13 20:26 <3ThomasBorregaardSorensen!!
// Mummy prepared - hinted that was sort of easy, lot of steps though :)
// Fish with Lemon, Tofu with premium soy sauce, grind ginger and chive, 
// japanese rice, fried egg-plant, some see weed leafs and cola extra coffee.
#pragma once


#include  "acme/prototype/collection/string_array.h"
#include "acme/filesystem/filesystem/path.h"
#include  "acme/prototype/prototype/atom.h"


namespace file
{


   class CLASS_DECL_ACME path_array_base :
      public ::string_base_array < ::file::path, string, e_type_string_array >
   {
   public:

      using BASE_ARRAY = ::string_base_array < ::file::path, string, e_type_string_array >;


      using BASE_ARRAY::BASE_ARRAY;
      using BASE_ARRAY::operator =;


      //using ::string_base_array < ::file::path, string, e_type_string_array >::string_base_array;


      // path_array(){}
      // path_array(const ::file::path_array_base & array):
      //    ::string_base_array < ::file::path, string, e_type_string_array >(array)
      // {}
      // path_array(::file::path_array_base&& array) :
      //    ::string_base_array < ::file::path, string, e_type_string_array >(::transfer(array))
      // {
      // }
      //~path_array() override {}


      virtual void patch_base_path(const ::file::path & pathBase);


      // path_array& operator=(const ::file::path_array_base& array)
      // {
      //
      //    ::string_base_array < ::file::path, string, e_type_string_array >::operator =(array);
      //
      //    return *this;
      //
      // }
      //
      //
      // path_array& operator=(::file::path_array_base&& array)
      // {
      //
      //    ::string_base_array < ::file::path, string, e_type_string_array >::operator =(::transfer(array));
      //
      //    return *this;
      //
      // }


   };


   class CLASS_DECL_ACME path_array :
      public ::array_particle < ::file::path_array_base >
   {
   public:


      using BASE_ARRAY = ::array_particle< ::file::path_array_base >;


      using BASE_ARRAY::BASE_ARRAY;
      using BASE_ARRAY::operator =;


   };


} // namespace file


template < primitive_array ARRAY >
inline ::file::path_array_base operator / (const ::file::path & pathBase, const ARRAY & straRelativeItems)
{

   ::file::path_array_base a;

   for (auto & strRelative : straRelativeItems)
   {

      a.add(pathBase / strRelative);

   }

   return ::transfer(a);

}



CLASS_DECL_ACME ::file::path_array_base & ascendants_path(const ::file::path & pathBase, ::file::path_array_base & pathaFolder, ::file::path_array_base * ppathaRelative = nullptr);
CLASS_DECL_ACME ::file::path_array_base ascendants_path(const ::file::path & pathBase);
CLASS_DECL_ACME ::file::path_array_base & ascendants_path(::file::path_array_base & patha, const ::file::path& pathBase);
CLASS_DECL_ACME ::string_array_base ascendants_name(const ::file::path & pathBase);
CLASS_DECL_ACME ::string_array_base & ascendants_name(::string_array_base & stra, const ::file::path& pathBase);



