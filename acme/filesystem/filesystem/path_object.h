﻿#pragma once


#include "acme/primitive/primitive/property_object.h"
#include "path.h"


namespace file
{


   class CLASS_DECL_ACME path_object :
      virtual public property_object,
      virtual public path
   {
   public:

      path_object();
      path_object(::matter*);
      path_object(const ::file::path& path);
      path_object(::file::path&& path);

      ~path_object() override;


      //virtual void exchange(::stream& s) override;

      virtual strsize sz_len() const override;
      virtual void to_sz(char* sz, strsize size) const override;
      
      using matter::set;
      using matter::has;

      using path::set;
      using path::has;

   };


   using path_pointer = ::pointer<path_object>;


} // namespace file



