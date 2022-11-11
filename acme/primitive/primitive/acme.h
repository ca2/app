#pragma once


namespace acme
{


   inline bool is_false(const char * psz);
   inline bool is_true(const char * psz);
   inline bool is_set_false(const char * psz);
   inline bool is_set_true(const char * psz);


   template < typename TYPE >
   ::pointer<TYPE>clone(const TYPE & t) { return __new(TYPE(t)); }


} // namespace acme



