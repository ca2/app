#include "framework.h"


namespace file
{


   path_object::~path_object()
   {

   }


   //void path_object::exchange(::stream& s)
   //{

   //   s.exchange(id::type_null, (::file::path&) * this);

   //}


   strsize path_object::sz_len() const
   {

      return get_length();

   }

   
   void path_object::to_sz(char* sz, strsize len) const
   {

      strncpy(sz, c_str(), len);

   }


   void path_object::to_string(string& str) const
   {

      str = (const string&)*this;

   }


} // namespace file



