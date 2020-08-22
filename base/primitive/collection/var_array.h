#pragma once


class CLASS_DECL_AURA var_array :
   public array < var >
{
public:


   var_array();
   var_array(const std::initializer_list < var > & varlist);
   var_array(const string_array & stra);
   var_array(const int_array & inta);
   var_array(const ::property_set & propset);
   var_array(const var_array & vara);
   virtual ~var_array();


   index add(const var & var);
   index add(const var_array & vara);
   index add(const std::initializer_list < var > & list)
   {

      ::index i = -1;

      for(auto & var : list)
      {

         auto iItem = add(var);

         if(i < 0) i = iItem;

      }

      return i;

   }

   inline index add(const string & str) { return add((const var &) str); }
   inline index add(const char * psz) { return add((const string &) psz); }

   inline index add(i8 i) { return add((const var &) i); }
   inline index add(u8 u) { return add((const var &) u); }
   inline index add(i16 i) { return add((const var &) i); }
   inline index add(u16 u) { return add((const var &) u); }
   inline index add(i32 i) { return add((const var &) i); }
   inline index add(u32 u) { return add((const var &) u); }
   inline index add(i64 i) { return add((const var &) i); }
   inline index add(u64 u) { return add((const var &) u); }

   ::count add_unique(const var_array & vara);

   string implode(const char * pszGlue) const;


   index find_first_ci(const char * psz, index find = 0, index last = -1) const;
   index find_first(const char * psz, index find = 0, index last = -1) const;
   index find_first(const var & var, index find = 0, index last = -1) const;

   bool contains_ci(const char * pcsz, index find = 0, index last = -1, ::count countMin = 1, ::count countMax = -1) const;

   bool contains(const char * pcsz, index find = 0, index last = -1, ::count countMin = 1, ::count countMax = -1) const;

   bool contains(const var & var, index find = 0, index last = -1, ::count countMin = 1, ::count countMax = -1) const;

   ::count remove_first_ci(const char * pcsz, index find = 0, index last = -1);

   ::count remove_first(const char * pcsz, index find = 0, index last = -1);

   ::count remove_first(const var & var, index find = 0, index last = -1);

   ::count remove_ci(const char * pcsz, index find = 0, index last = -1, ::count countMin = 0, ::count countMax = -1);

   ::count remove(const char * pcsz, index find = 0, index last = -1, ::count countMin = 0, ::count countMax = -1);

   ::count remove(const var & var, index find = 0, index last = -1, ::count countMin = 0, ::count countMax = -1);

   ::count remove(const var_array & vara);

   var_array & operator -=(var var);
   var_array & operator -=(var_array vara);
   var_array operator -(var var) const;
   var_array operator -(var_array vara) const;
   var_array & operator +=(var var);
   var_array & operator +=(var_array vara);
   var_array operator +(var var) const;
   var_array operator +(var_array vara) const;

   var_array & operator = (const string_array & stra);
   var_array & operator = (const int_array & inta);
   var_array & operator = (const ::property_set & propset);
   var_array & operator = (const var_array & vara);


   void parse_json(const char * & pszJson);
   void parse_json(const char * & pszJson, const char * pszEnd);

   void find_json_child(const char * & pszJson, const char * pszEnd, const var & var);


   string & get_json(string & str, bool bNewLine = true) const;


   var_array array()
   {

      return var_array();

   }

   template < typename... VARS >
   var_array array(VARS&... vars)
   {

      var_array va;
      return va.array(vars...);

   }


   inline var value_at(::index i) const;


};


CLASS_DECL_AURA void var_array_skip_json(const char *& pszJson);
CLASS_DECL_AURA void var_array_skip_json(const char *& pszJson, const char * pszEnd);


inline var var_array::value_at(::index i) const
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
   ::var_array array_merge(VARS&... vars)
   {

      return ::var_array().array(vars...);


   }


} // namespace papaya



