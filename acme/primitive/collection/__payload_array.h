#pragma once


// Include payload.h
// Don`t include this file directly


#include "array.h"


class CLASS_DECL_ACME payload_array :
   public array < ::payload, const ::payload &, ::allocator::def < ::payload >, e_type_payload_array >
{
public:


   using BASE_ARRAY = array < ::payload, const ::payload&, ::allocator::def < ::payload >, e_type_payload_array >;


   payload_array();
   payload_array(const std::initializer_list < ::payload > & varlist);
   payload_array(const string_array & stra);
   payload_array(const int_array & inta);
   payload_array(const ::property_set & propset);
   payload_array(const payload_array & payloada);
   ~payload_array() override;


   index add(const ::payload & payload);
   index append(const payload_array & payloada);
   index append(const std::initializer_list < ::payload > & list);

   inline index add(const ::string & str) { return add((const ::payload &) str); }
   inline index add(const ::scoped_string & scopedstr) { return add((const string &) scopedstr); }

   inline index add(i8 i) { return add((const ::payload &) i); }
   inline index add(u8 u) { return add((const ::payload &) u); }
   inline index add(i16 i) { return add((const ::payload &) i); }
   inline index add(u16 u) { return add((const ::payload &) u); }
   inline index add(i32 i) { return add((const ::payload &) i); }
   inline index add(u32 u) { return add((const ::payload &) u); }
   inline index add(i64 i) { return add((const ::payload &) i); }
   inline index add(u64 u) { return add((const ::payload &) u); }

   ::count append_unique(const payload_array & payloada);

   string implode(const ::scoped_string & scopedstrGlue) const;


   index find_first_ci(const ::scoped_string & scopedstr, index find = 0, index last = -1) const;
   index find_first(const ::scoped_string & scopedstr, index find = 0, index last = -1) const;
   index find_first(const ::payload & payload, index find = 0, index last = -1) const;

   bool case_insensitive_contains(const ::scoped_string & str, index find = 0, index last = -1, ::count countMin = 1, ::count countMax = -1) const;

   bool contains(const ::scoped_string & str, index find = 0, index last = -1, ::count countMin = 1, ::count countMax = -1) const;

   bool contains(const ::payload & payload, index find = 0, index last = -1, ::count countMin = 1, ::count countMax = -1) const;


   std::strong_ordering operator<=>(const ::payload_array & payloada) const
   {

      return order(payloada);

   }

   std::strong_ordering order(const ::payload_array & payloada) const;
   std::strong_ordering case_insensitive_order(const ::payload_array & payloada) const;

   ::count erase_first_ci(const ::scoped_string & str, index find = 0, index last = -1);

   ::count erase_first(const ::scoped_string & str, index find = 0, index last = -1);

   ::count erase_first(const ::payload & payload, index find = 0, index last = -1);

   ::count erase_ci(const ::scoped_string & str, index find = 0, index last = -1, ::count countMin = 0, ::count countMax = -1);

   ::count erase(const ::scoped_string & str, index find = 0, index last = -1, ::count countMin = 0, ::count countMax = -1);

   ::count erase(const ::payload & payload, index find = 0, index last = -1, ::count countMin = 0, ::count countMax = -1);

   ::count erase(const payload_array & payloada);

   payload_array & operator -=(const ::payload & payload);
   payload_array & operator -=(const payload_array & payloada);
   payload_array operator -(const ::payload & payload) const;
   payload_array operator -(const payload_array & payloada) const;
   payload_array & operator +=(const ::payload & payload);
   payload_array & operator +=(const payload_array & payloada);
   payload_array operator +(const ::payload & payload) const;
   payload_array operator +(const payload_array & payloada) const;

   payload_array & operator = (const string_array & stra);
   payload_array & operator = (const int_array & inta);
   payload_array & operator = (const ::property_set & propset);
   payload_array & operator = (const payload_array & payloada);


   //void parse_network_payload(const char * & pszJson);
   void parse_network_payload(::const_ansi_range & range);
   void find_network_payload_child(::const_ansi_range & range, const ::payload & payload);


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


   inline ::payload value_at(::index i) const;


   string_array stra() const
   {

      string_array stra;

      for (auto & item : *this)
      {

         stra.add(item.get_string());

      }

      return ::transfer(stra);

   }


};


inline std::strong_ordering payload_array::order(const ::payload_array & payloada) const
{

   auto iMinimumSize = minimum(this->size(), payloada.size());

   for (index i = 0; i < iMinimumSize; i++)
   {

      auto ordering = element_at(i).order(payloada.element_at(i));

      if (ordering != 0)
      {

         return ordering;

      }

   }

   return this->size() <=> payloada.size();

}


inline std::strong_ordering payload_array::case_insensitive_order(const ::payload_array & payloada) const
{

   return stra().case_insensitive_order(payloada.stra());

}


//CLASS_DECL_ACME void var_array_skip_network_payload(const char *& pszJson);
CLASS_DECL_ACME void var_array_skip_network_payload(::const_ansi_range & range);


inline ::payload payload_array::value_at(::index i) const
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



