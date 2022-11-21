#pragma once


#include "acme/primitive/primitive/particle.h"
#include  "acme/primitive/primitive/pointer.h"
#include "path.h"


namespace file
{


   class path_object :
      public particle,
      public path
   {
   public:

      path_object();
      path_object(::matter*);
      path_object(const ::file::path& path);
      path_object(::file::path&& path);

      ~path_object() override;


      virtual strsize sz_len() const override;
      virtual void to_sz(char* sz, strsize size) const override;
      
      //using matter::set_flag;
      //using matter::has_flag;

      using path::set;
      using path::has;

   };


   using path_pointer = ::pointer<path_object>;


} // namespace file




namespace file
{


   //interlocked_count g_interlockedcountFilePathObject;


   inline path_object::path_object()
   {

      // g_interlockedcountFilePathObject++;

       //::output_debug_string("----::file::path_object (count=" + as_string(g_interlockedcountFilePathObject.operator long long()) + ")\n");

   }


   inline path_object::path_object(::matter*)
   {

      //g_interlockedcountFilePathObject++;

      //::output_debug_string("----::file::path_object (count=" + as_string(g_interlockedcountFilePathObject.operator long long()) + ")\n");

   }


   inline path_object::path_object(const ::file::path& path) :
      ::file::path(path)
   {

      //g_interlockedcountFilePathObject++;

      //::output_debug_string("----::file::path_object (count=" + as_string(g_interlockedcountFilePathObject.operator long long()) + ")\n");

   }


   inline path_object::path_object(::file::path&& path) :
      ::file::path(::move(path))
   {

      //g_interlockedcountFilePathObject++;

      //::output_debug_string("----::file::path_object (count=" + as_string(g_interlockedcountFilePathObject.operator long long()) + ")\n");

   }


   inline path_object::~path_object()
   {

      //g_interlockedcountFilePathObject--;

   }


   /*void path_object::exchange(::stream& s)
   {

      s.exchange(atom::e_type_null, (::file::path&) * this);

   }*/


   inline strsize path_object::sz_len() const
   {

      return get_length() + 1;

   }


   inline void path_object::to_sz(char* sz, strsize len) const
   {

      strncpy(sz, c_str(), len);

   }


   //string path_object::to_string() const
   //{

   //   return (::string) *this;

   //}


} // namespace file






