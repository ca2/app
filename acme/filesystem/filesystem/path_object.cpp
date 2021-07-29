#include "framework.h"


namespace file
{


   interlocked_count g_interlockedcountFilePathObject;


   path_object::path_object() 
   {
   
      g_interlockedcountFilePathObject++;

      //::output_debug_string("----::file::path_object (count=" + __str(g_interlockedcountFilePathObject.operator long long()) + ")\n");

   }


   path_object::path_object(::matter*)
   {

      g_interlockedcountFilePathObject++;

      //::output_debug_string("----::file::path_object (count=" + __str(g_interlockedcountFilePathObject.operator long long()) + ")\n");
   
   }


   path_object::path_object(const ::file::path& path) :
      ::file::path(path) 
   {

      g_interlockedcountFilePathObject++;

      //::output_debug_string("----::file::path_object (count=" + __str(g_interlockedcountFilePathObject.operator long long()) + ")\n");
   
   }


   path_object::path_object(::file::path&& path) :
      ::file::path(::move(path)) 
   {

      g_interlockedcountFilePathObject++;

      //::output_debug_string("----::file::path_object (count=" + __str(g_interlockedcountFilePathObject.operator long long()) + ")\n");
   
   }


   path_object::~path_object()
   {

      g_interlockedcountFilePathObject--;

   }


   void path_object::exchange(::stream& s)
   {

      s.exchange(id::e_type_null, (::file::path&) * this);

   }


   strsize path_object::sz_len() const
   {

      return get_length();

   }

   
   void path_object::to_sz(char* sz, strsize len) const
   {

      strncpy(sz, c_str(), len);

   }


   void path_object::to_string(const class string_exchange & str) const
   {

      str = (const string&)*this;

   }


} // namespace file



