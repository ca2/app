// Created by camilo on 2022-03-13 20:26 <3ThomasBorregaardSorensen!!
// Mummy prepared - hinted that was sort of easy, lot of steps though :)
// Fish with Lemon, Tofu with premium soy sauce, grind ginger and chive, 
// japanese rice, fried egg-plant, some see weed leafs and cola extra coffee.
#pragma once


#include  "acme/prototype/collection/string_array.h"
#include "path.h"
#include  "acme/prototype/prototype/atom.h"


namespace file
{


   class CLASS_DECL_ACME path_array :
      virtual public ::string_array_base < ::file::path, string, e_type_string_array >
   {
   public:


      path_array(){}
      path_array(const ::file::path_array & array):
         ::string_array_base < ::file::path, string, e_type_string_array >(array)
      {}
      path_array(::file::path_array&& array) :
         ::string_array_base < ::file::path, string, e_type_string_array >(::transfer(array))
      {
      }
      ~path_array() override {}


      virtual void patch_base_path(const ::file::path & pathBase);


      path_array& operator=(const ::file::path_array& array)
      {
         ::string_array_base < ::file::path, string, e_type_string_array >::operator =(array);
            return *this;
      }

      path_array& operator=(::file::path_array&& array)
      {
         ::string_array_base < ::file::path, string, e_type_string_array >::operator =(::transfer(array));
         return *this;
      }

   };

//   inline path_array path::ascendants_path() const { path_array patha; return ascendants_path(patha); }



} // namespace file


//inline void __exchange(::payload_stream & stream, ::file::path_array & array);


CLASS_DECL_ACME ::file::path_array operator / (const ::file::path & pathBase, const string_array & straRelativeItems);
CLASS_DECL_ACME ::file::path_array & ascendants_path(const ::file::path & pathBase, ::file::path_array & pathaFolder, ::file::path_array * ppathaRelative = nullptr);
CLASS_DECL_ACME ::file::path_array ascendants_path(const ::file::path & pathBase);
CLASS_DECL_ACME ::file::path_array & ascendants_path(::file::path_array & patha, const ::file::path& pathBase);
CLASS_DECL_ACME ::string_array ascendants_name(const ::file::path & pathBase);
CLASS_DECL_ACME ::string_array & ascendants_name(::string_array & stra, const ::file::path& pathBase);



