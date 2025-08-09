#pragma once


// Include payload.h
// Don`t include this file directly


#include "array_base.h"


class CLASS_DECL_ACME payload_array_base :
   public array_base < ::payload, const ::payload &, ::typed::def < ::payload >, ::heap::typed_memory < ::payload, ::heap::e_memory_array >, e_type_payload_array >
{
public:


   using BASE_ARRAY = array_base < ::payload, const ::payload&, ::typed::def < ::payload >, ::heap::typed_memory < ::payload, ::heap::e_memory_array >, e_type_payload_array >;


   payload_array_base();
   payload_array_base(const std::initializer_list < ::payload > & varlist);
   payload_array_base(const string_array & stra);
   payload_array_base(const ::int_array & inta);
   payload_array_base(const ::property_set & propset);
   payload_array_base(const payload_array_base & payloada);
   payload_array_base(payload_array_base && payloada);
   ~payload_array_base();


   ::collection::index add(const ::payload & payload);
   ::collection::index append(const payload_array_base & payloada);
   ::collection::index append(const std::initializer_list < ::payload > & list);

//   inline ::collection::index add(const ::scoped_string & scopedstr) { return add((const ::payload &) str); }
   //inline ::collection::index add(const ::scoped_string & scopedstr) { return add((const payload &) scopedstr); }

   //inline ::collection::index add(char ch) { return add((const ::payload &) ch); }
   //inline ::collection::index add(unsigned char uch) { return add((const ::payload &) uch); }
   //inline ::collection::index add(short sh) { return add((const ::payload &) sh); }
   //inline ::collection::index add(unsigned short ush) { return add((const ::payload &) ush); }
   //inline ::collection::index add(int i) { return add((const ::payload &) i); }
   //inline ::collection::index add(unsigned int ui) { return add((const ::payload &) ui); }
   //inline ::collection::index add(long long hi) { return add((const ::payload &) hi); }
   //inline ::collection::index add(unsigned long long hn) { return add((const ::payload &) hn); }

   ::collection::count append_unique(const payload_array_base & payloada);

   string implode(const ::scoped_string & scopedstrGlue) const;


   ::collection::index case_insensitive_find_first(const ::scoped_string & scopedstr, ::collection::index find = 0, ::collection::index last = -1) const;
   ::collection::index find_first(const ::scoped_string & scopedstr, ::collection::index find = 0, ::collection::index last = -1) const;
   ::collection::index find_first(const ::payload & payload, ::collection::index find = 0, ::collection::index last = -1) const;

   bool case_insensitive_contains(const ::scoped_string & str, ::collection::index find = 0, ::collection::index last = -1, ::collection::count countMin = 1, ::collection::count countMax = -1) const;

   bool contains(const ::scoped_string & str, ::collection::index find = 0, ::collection::index last = -1, ::collection::count countMin = 1, ::collection::count countMax = -1) const;

   bool contains(const ::payload & payload, ::collection::index find = 0, ::collection::index last = -1, ::collection::count countMin = 1, ::collection::count countMax = -1) const;


   std::strong_ordering operator<=>(const ::payload_array_base & payloada) const
   {

      return order(payloada);

   }

   std::strong_ordering order(const ::payload_array_base & payloada) const;
   std::strong_ordering case_insensitive_order(const ::payload_array_base & payloada) const;

   ::collection::count case_insensitive_erase_first(const ::scoped_string & str, ::collection::index find = 0, ::collection::index last = -1);

   ::collection::count erase_first(const ::scoped_string & str, ::collection::index find = 0, ::collection::index last = -1);

   ::collection::count erase_first(const ::payload & payload, ::collection::index find = 0, ::collection::index last = -1);

   ::collection::count case_insensitive_erase(const ::scoped_string & str, ::collection::index find = 0, ::collection::index last = -1, ::collection::count countMin = 0, ::collection::count countMax = -1);

   ::collection::count erase(const ::scoped_string & str, ::collection::index find = 0, ::collection::index last = -1, ::collection::count countMin = 0, ::collection::count countMax = -1);

   ::collection::count erase(const ::payload & payload, ::collection::index find = 0, ::collection::index last = -1, ::collection::count countMin = 0, ::collection::count countMax = -1);

   ::collection::count erase(const payload_array_base & payloada);

   payload_array_base & operator -=(const ::payload & payload);
   payload_array_base & operator -=(const payload_array_base & payloada);
   payload_array_base operator -(const ::payload & payload) const;
   payload_array_base operator -(const payload_array_base & payloada) const;
   payload_array_base & operator +=(const ::payload & payload);
   payload_array_base & operator +=(const payload_array_base & payloada);
   payload_array_base operator +(const ::payload & payload) const;
   payload_array_base operator +(const payload_array_base & payloada) const;

   payload_array_base & operator = (const string_array & stra);
   payload_array_base & operator = (const ::int_array & inta);
   payload_array_base & operator = (const ::property_set & propset);
   payload_array_base & operator = (const payload_array_base & payloada);


   //void parse_network_payload(const_char_pointer &pszJson);
   void parse_network_payload(::ansi_range & range);
   void find_network_payload_child(::ansi_range & range, const ::payload & payload);


   string & get_network_payload(string & str, bool bNewLine = true) const;

   //
   // payload_array_base array()
   // {
   //
   //    return payload_array_base();
   //
   // }
   //
   // template < typename... VARS >
   // payload_array_base array(VARS&... vars)
   // {
   //
   //    payload_array_base va;
   //    return va.array(vars...);
   //
   // }
   //

   inline ::payload value_at(::collection::index i) const;


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




//CLASS_DECL_ACME void var_array_skip_network_payload(const_char_pointer &pszJson);
CLASS_DECL_ACME void payload_array_skip_network_payload(::ansi_range & range);


inline ::payload payload_array_base::value_at(::collection::index i) const
{

   if (i < 0 || i >= this->get_count())
   {

      return error_index_out_of_bounds;

   }

   return this->element_at(i);

}


class payload_array :
   public ::array_particle < payload_array_base >
{
public:


   using BASE_ARRAY = ::array_particle< payload_array_base >;


   using BASE_ARRAY::BASE_ARRAY;
   using BASE_ARRAY::operator =;


};


namespace acme
{


   template < typename... VARS >
   ::payload_array array_merge(VARS&... vars)
   {

      return ::payload_array(vars...);


   }


} // namespace acme






