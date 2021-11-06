#pragma once


namespace papaya
{


   inline bool is_false(const char * psz);
   inline bool is_true(const char * psz);
   inline bool is_set_false(const char * psz);
   inline bool is_set_true(const char * psz);


   inline bool is_false(const ::string & str);
   inline bool is_true(const ::string & str);
   inline bool is_set_false(const ::string & str);
   inline bool is_set_true(const ::string & str);


   template < typename TYPE >
   __pointer(TYPE) clone(const TYPE & t) { return __new(TYPE(t)); }


} // namespace papaya



