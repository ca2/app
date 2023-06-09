// Created by camilo on 2022-03-13 19:38 <3ThomasBorregaardSorensen!!
// Mummy prepared - hinted that was sort of easy, lot of steps though :)
// Fish with Lemon, Tofu with premium soy sauce, grind ginger and chive, 
// japanese rice, fried egg-plant, some see weed leafs and cola extra coffee.
#pragma once


#include "acme/primitive/primitive/particle.h"


namespace file
{


   class CLASS_DECL_ACME enumerator :
      virtual public ::particle
   {

   public:


      enumerator() {}
      ~enumerator() override {}


   //protected:


   //   //virtual bool _enumerates(::file::listing & listing) = 0;


   //   virtual bool _enumerate(listing & listing) = 0;


   //public:


      // returns true if it can do and have done enumeration for the 
      // source m_pathUser member in the listing.
      // returns false the enumerator is not a enumerator for the
      // source m_pathUser member in the listing.
      // throws exception if listing enumeration fails for some reason.
      virtual bool enumerate(listing & listing);

      virtual bool list(string_array & stra, const ::scoped_string & scopedstr, ::file::e_flag eflag = ::file::e_flag_file_or_folder);


      //virtual bool enumerate(::file::listing & listing, const ::file::path & path, ::file::e_flag eflag = ::file::e_flag_none, enum_depth edepth = e_depth_none);
      //virtual bool enumerate_pattern(::file::listing & listing, const ::file::path & path, const ::string_array & straPattern, ::file::e_flag eflag = ::file::e_flag_none, enum_depth edepth = e_depth_none);


   };


} // namespace file



