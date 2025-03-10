#pragma once


#include "acme/prototype/prototype/pointer.h"
#include "path.h"


namespace file
{


   class path_object :
      public particle,
      public path
   {
   public:

      path_object();
      //path_object(::matter*);
      path_object(const ::file::path_object & pathobject):path_object((const::file::path & )pathobject){}
      path_object(const ::file::path& path);
      path_object(::file::path&& path);
      ~path_object() override;


      virtual character_count sz_len() const override;
      virtual void to_sz(char* sz, character_count size) const override;
      
      //using matter::set_flag;
      //using matter::has_flag;

      //using path::set;
      //using path::has;

   };


   using path_pointer = ::pointer<path_object>;


} // namespace file




namespace file
{


   //interlocked_count g_interlockedcountFilePathObject;


   inline path_object::path_object()
   {

      // g_interlockedcountFilePathObject++;

       //informationf("----::file::path_object (count=" + as_string(g_interlockedcountFilePathObject.operator long long) + ")\n");

   }


   //inline path_object::path_object(::matter*)
   //{

   //   //g_interlockedcountFilePathObject++;

   //   //informationf("----::file::path_object (count=" + as_string(g_interlockedcountFilePathObject.operator long long) + ")\n");

   //}


   inline path_object::path_object(const ::file::path& path) :
      ::file::path(path)
   {

      //g_interlockedcountFilePathObject++;

      //informationf("----::file::path_object (count=" + as_string(g_interlockedcountFilePathObject.operator long long) + ")\n");

   }


   inline path_object::path_object(::file::path&& path) :
      ::file::path(::transfer(path))
   {

      //g_interlockedcountFilePathObject++;

      //informationf("----::file::path_object (count=" + as_string(g_interlockedcountFilePathObject.operator long long) + ")\n");

   }


   inline path_object::~path_object()
   {

      //g_interlockedcountFilePathObject--;

   }


   /*void path_object::exchange(::stream& s)
   {

      s.exchange(atom::e_type_null, (::file::path&) * this);

   }*/


   inline character_count path_object::sz_len() const
   {

      return length() + 1;

   }


   inline void path_object::to_sz(char* sz, character_count len) const
   {

      ansi_ncpy(sz, c_str(), len);

   }


   //string path_object::to_string() const
   //{

   //   return (::string) *this;

   //}


} // namespace file






