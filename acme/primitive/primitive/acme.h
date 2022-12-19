#pragma once


namespace acme
{


   inline bool is_false(const scoped_string & str);
   inline bool is_true(const scoped_string & str);
   inline bool is_set_false(const scoped_string & str);
   inline bool is_set_true(const scoped_string & str);


   template < typename TYPE >
   ::pointer<TYPE>clone(const TYPE & t) { return __new(TYPE(t)); }


} // namespace acme



