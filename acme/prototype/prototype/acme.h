#pragma once


namespace acme
{


   inline bool is_false(const ::scoped_string & scopedstr);
   inline bool is_true(const ::scoped_string & scopedstr);
   inline bool is_set_false(const ::scoped_string & scopedstr);
   inline bool is_set_true(const ::scoped_string & scopedstr);


   template < typename TYPE >
   ::pointer<TYPE>clone(const TYPE & t) { return øallocate TYPE(t); }


} // namespace acme



