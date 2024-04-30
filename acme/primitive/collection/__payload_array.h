#pragma once


// Include payload.h
// Don`t include this file directly


#include "array.h"


class CLASS_DECL_ACME payload_array :
   public array < ::payload, const ::payload &, ::typed::def < ::payload >, ::heap::typed_memory < ::payload, ::heap::e_memory_array >, e_type_payload_array >
{
public:


   using BASE_ARRAY = array < ::payload, const ::payload&, ::typed::def < ::payload >, ::heap::typed_memory < ::payload, ::heap::e_memory_array >, e_type_payload_array >;


   payload_array();
   payload_array(const std::initializer_list < ::payload > & varlist);
   payload_array(const string_array & stra);
   payload_array(const ::i32_array & inta);
   payload_array(const ::property_set & propset);
   payload_array(const payload_array & payloada);
   ~payload_array() override;


   ::raw::index add(const ::payload & payload);
   ::raw::index append(const payload_array & payloada);
   ::raw::index append(const std::initializer_list < ::payload > & list);

   inline ::raw::index add(const ::string & str) { return add((const ::payload &) str); }
   inline ::raw::index add(const ::scoped_string & scopedstr) { return add((const string &) scopedstr); }

   inline ::raw::index add(i8 i) { return add((const ::payload &) i); }
   inline ::raw::index add(u8 u) { return add((const ::payload &) u); }
   inline ::raw::index add(i16 i) { return add((const ::payload &) i); }
   inline ::raw::index add(u16 u) { return add((const ::payload &) u); }
   inline ::raw::index add(i32 i) { return add((const ::payload &) i); }
   inline ::raw::index add(u32 u) { return add((const ::payload &) u); }
   inline ::raw::index add(i64 i) { return add((const ::payload &) i); }
   inline ::raw::index add(u64 u) { return add((const ::payload &) u); }

   ::raw::count append_unique(const payload_array & payloada);

   string implode(const ::scoped_string & scopedstrGlue) const;


   ::raw::index find_first_ci(const ::scoped_string & scopedstr, ::raw::index find = 0, ::raw::index last = -1) const;
   ::raw::index find_first(const ::scoped_string & scopedstr, ::raw::index find = 0, ::raw::index last = -1) const;
   ::raw::index find_first(const ::payload & payload, ::raw::index find = 0, ::raw::index last = -1) const;

   bool case_insensitive_contains(const ::scoped_string & str, ::raw::index find = 0, ::raw::index last = -1, ::raw::count countMin = 1, ::raw::count countMax = -1) const;

   bool contains(const ::scoped_string & str, ::raw::index find = 0, ::raw::index last = -1, ::raw::count countMin = 1, ::raw::count countMax = -1) const;

   bool contains(const ::payload & payload, ::raw::index find = 0, ::raw::index last = -1, ::raw::count countMin = 1, ::raw::count countMax = -1) const;


   std::strong_ordering operator<=>(const ::payload_array & payloada) const
   {

      return order(payloada);

   }

   std::strong_ordering order(const ::payload_array & payloada) const;
   std::strong_ordering case_insensitive_order(const ::payload_array & payloada) const;

   ::raw::count erase_first_ci(const ::scoped_string & str, ::raw::index find = 0, ::raw::index last = -1);

   ::raw::count erase_first(const ::scoped_string & str, ::raw::index find = 0, ::raw::index last = -1);

   ::raw::count erase_first(const ::payload & payload, ::raw::index find = 0, ::raw::index last = -1);

   ::raw::count erase_ci(const ::scoped_string & str, ::raw::index find = 0, ::raw::index last = -1, ::raw::count countMin = 0, ::raw::count countMax = -1);

   ::raw::count erase(const ::scoped_string & str, ::raw::index find = 0, ::raw::index last = -1, ::raw::count countMin = 0, ::raw::count countMax = -1);

   ::raw::count erase(const ::payload & payload, ::raw::index find = 0, ::raw::index last = -1, ::raw::count countMin = 0, ::raw::count countMax = -1);

   ::raw::count erase(const payload_array & payloada);

   payload_array & operator -=(const ::payload & payload);
   payload_array & operator -=(const payload_array & payloada);
   payload_array operator -(const ::payload & payload) const;
   payload_array operator -(const payload_array & payloada) const;
   payload_array & operator +=(const ::payload & payload);
   payload_array & operator +=(const payload_array & payloada);
   payload_array operator +(const ::payload & payload) const;
   payload_array operator +(const payload_array & payloada) const;

   payload_array & operator = (const string_array & stra);
   payload_array & operator = (const ::i32_array & inta);
   payload_array & operator = (const ::property_set & propset);
   payload_array & operator = (const payload_array & payloada);


   //void parse_network_payload(const char * & pszJson);
   void parse_network_payload(::ansi_range & range);
   void find_network_payload_child(::ansi_range & range, const ::payload & payload);


   string & get_network_payload(string & str, bool bNewLine = true) const;


   payload_array array()
   {

      return payload_array();

   }

   template < typename... VARS >
   payload_array array(VARS&... vars)
   {

      payload_array va;
      return va.array(vars...);

   }


   inline ::payload value_at(::raw::index i) const;


   string_array stra() const
   {

      string_array stra;

      for (auto & item : *this)
      {

         stra.add(item.as_string());

      }

      return ::transfer(stra);

   }


};




//CLASS_DECL_ACME void var_array_skip_network_payload(const char *& pszJson);
CLASS_DECL_ACME void payload_array_skip_network_payload(::ansi_range & range);


inline ::payload payload_array::value_at(::raw::index i) const
{

   if (i < 0 || i >= this->get_count())
   {

      return error_index_out_of_bounds;

   }

   return this->element_at(i);

}


namespace acme
{


   template < typename... VARS >
   ::payload_array array_merge(VARS&... vars)
   {

      return ::payload_array().array(vars...);


   }


} // namespace acme



