#pragma once


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
   index add(const payload_array & payloada);
   index add(const std::initializer_list < ::payload > & list)
   {

      ::index i = -1;

      for(auto & payload : list)
      {

         auto iItem = add(payload);

         if(i < 0) i = iItem;

      }

      return i;

   }

   inline index add(const string & str) { return add((const ::payload &) str); }
   inline index add(const char * psz) { return add((const string &) psz); }

   inline index add(i8 i) { return add((const ::payload &) i); }
   inline index add(u8 u) { return add((const ::payload &) u); }
   inline index add(i16 i) { return add((const ::payload &) i); }
   inline index add(u16 u) { return add((const ::payload &) u); }
   inline index add(i32 i) { return add((const ::payload &) i); }
   inline index add(u32 u) { return add((const ::payload &) u); }
   inline index add(i64 i) { return add((const ::payload &) i); }
   inline index add(u64 u) { return add((const ::payload &) u); }

   ::count add_unique(const payload_array & payloada);

   string implode(const char * pszGlue) const;


   index find_first_ci(const char * psz, index find = 0, index last = -1) const;
   index find_first(const char * psz, index find = 0, index last = -1) const;
   index find_first(const ::payload & payload, index find = 0, index last = -1) const;

   bool contains_ci(const char * pcsz, index find = 0, index last = -1, ::count countMin = 1, ::count countMax = -1) const;

   bool contains(const char * pcsz, index find = 0, index last = -1, ::count countMin = 1, ::count countMax = -1) const;

   bool contains(const ::payload & payload, index find = 0, index last = -1, ::count countMin = 1, ::count countMax = -1) const;

   ::count erase_first_ci(const char * pcsz, index find = 0, index last = -1);

   ::count erase_first(const char * pcsz, index find = 0, index last = -1);

   ::count erase_first(const ::payload & payload, index find = 0, index last = -1);

   ::count erase_ci(const char * pcsz, index find = 0, index last = -1, ::count countMin = 0, ::count countMax = -1);

   ::count erase(const char * pcsz, index find = 0, index last = -1, ::count countMin = 0, ::count countMax = -1);

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


   void parse_json(const char * & pszJson);
   void parse_json(const char * & pszJson, const char * pszEnd);

   void find_json_child(const char * & pszJson, const char * pszEnd, const ::payload & payload);


   string & get_json(string & str, bool bNewLine = true) const;


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


};


CLASS_DECL_ACME void var_array_skip_json(const char *& pszJson);
CLASS_DECL_ACME void var_array_skip_json(const char *& pszJson, const char * pszEnd);


inline ::payload payload_array::value_at(::index i) const
{

   if (i < 0 || i >= this->get_count())
   {

      return error_index_out_of_bounds;

   }

   return this->element_at(i);

}


namespace papaya
{


   template < typename... VARS >
   ::payload_array array_merge(VARS&... vars)
   {

      return ::payload_array().array(vars...);


   }


} // namespace papaya



