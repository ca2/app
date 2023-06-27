#include "framework.h"
//#include "path_object.h"

//
//namespace file
//{
//
//
//   //interlocked_count g_interlockedcountFilePathObject;
//
//
//   path_object::path_object() 
//   {
//   
//     // g_interlockedcountFilePathObject++;
//
//      //::information("----::file::path_object (count=" + as_string(g_interlockedcountFilePathObject.operator long long()) + ")\n");
//
//   }
//
//
//   path_object::path_object(::matter*)
//   {
//
//      //g_interlockedcountFilePathObject++;
//
//      //::information("----::file::path_object (count=" + as_string(g_interlockedcountFilePathObject.operator long long()) + ")\n");
//   
//   }
//
//
//   path_object::path_object(const ::file::path& path) :
//      ::file::path(path) 
//   {
//
//      //g_interlockedcountFilePathObject++;
//
//      //::information("----::file::path_object (count=" + as_string(g_interlockedcountFilePathObject.operator long long()) + ")\n");
//   
//   }
//
//
//   path_object::path_object(::file::path&& path) :
//      ::file::path(::transfer(path)) 
//   {
//
//      //g_interlockedcountFilePathObject++;
//
//      //::information("----::file::path_object (count=" + as_string(g_interlockedcountFilePathObject.operator long long()) + ")\n");
//   
//   }
//
//
//   path_object::~path_object()
//   {
//
//      //g_interlockedcountFilePathObject--;
//
//   }
//
//
//   /*void path_object::exchange(::stream& s)
//   {
//
//      s.exchange(atom::e_type_null, (::file::path&) * this);
//
//   }*/
//
//
//   strsize path_object::sz_len() const
//   {
//
//      return get_length() + 1;
//
//   }
//
//   
//   void path_object::to_sz(char* sz, strsize len) const
//   {
//
//      strncpy(sz, c_str(), len);
//
//   }
//
//
//   //string path_object::to_string() const
//   //{
//
//   //   return (::string) *this;
//
//   //}
//
//
//} // namespace file
//
//
//
