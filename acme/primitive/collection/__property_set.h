#pragma once


// Include payload.h
// Don`t include this file directly


#include "acme/primitive/primitive/__property.h"
//#include "payload_reference.h"


// property set key is case insensitive
// PROPERTY_ARRAY Property set ordered
class CLASS_DECL_ACME property_set :
   public property_ptra
{
public:


   using BASE_ARRAY = property_ptra;


   using property_ptra::erase;


   //__declare_iterator(name_iterator, &(*this->m_pelement)->m_atom);
   //__declare_iterator(value_iterator, &(*this->m_pelement)->m_var);


   property_set() { }
   property_set(::std::initializer_list < ::payload > list);
   property_set(const property_set & set);
   property_set(property_set && set);
   virtual ~property_set();


   ::count erase_by_name(const atom & idName);
   ::count erase_by_name(string_array & straName);

   virtual ::particle * source_channel();

   ::payload operator()(const atom & atom, const ::payload & varDefault = ::error_not_found) const;

   string _001Replace(const ::string & str) const;

   inline string format(const ::string & str) const { return _001Replace(str); }


   string as_string(const ::scoped_string& scopedstrSeparator1, const ::scoped_string& scopedstrSeparator2);

   ::index index_of(const ::atom & atom, ::index iStart = 0) const;


   property * find(const ::atom & atom, ::index iStart = 0) const;// { return atom.is_text() ? find_text_key((const ::scoped_string &)atom.m_str, iStart) : find_index(atom.m_i); }
   property & get(const ::atom & atom, ::index iStart = 0); // { return atom.is_text() ? get_text_key((const ::scoped_string &)atom.m_str, iStart) : get_index(atom.m_i); }

   
   //property * find_index(::iptr i) const;
   //property & get_index(::iptr i);


   //property * find_text_key(const scoped_string & scopedstr, ::index iStart = 0) const;
   //property & get_text_key(const scoped_string & scopedstr, ::index iStart = 0);


   //inline property * find_property_index(::index iIndex, ::index iStart = 0) const { return find_index(iIndex); }
   //inline property & get_property_index(::index iIndex, ::index iStart = 0) { return get_index(iIndex); }


   //inline property * find_property_text_key(const scoped_string & scopedstr, ::index iStart = 0) const { return find_text_key(scopedstr, iStart); }
   //inline property & get_property_text_key(const scoped_string & scopedstr, ::index iStart = 0) { return get_text_key(scopedstr, iStart); }


   //inline property * payload_index(::iptr iIndex, ::index iStart = 0) const { return find_property_index(iIndex); }
   //inline property & payload_index(::iptr iIndex, ::index iStart = 0) { return get_property_index(iIndex); }


   //inline property * payload_text_key(const scoped_string & scopedstr, ::index iStart = 0) const { return find_property_text_key(scopedstr, iStart); }
   //inline property & payload_text_key(const scoped_string & scopedstr, ::index iStart = 0) { return get_property_text_key(scopedstr, iStart); }



   inline ::payload operator[](const ::atom & atom) const { return find(atom); }
   inline ::property & operator[](const ::atom & atom) { return get(atom); }



   //template < character_range RANGE >
   //inline property & operator[](const RANGE & range) { return payload(r(const ::scoped_string_base &)range); }
   //template < character_range RANGE >
   //inline const property & operator[](const RANGE & range) const { return payload((const ::scoped_string_base &)range); }

   //template < has_get_string HAS_GET_STRING >
   //inline property & operator[](const HAS_GET_STRING & has_get_string) { return payload((const ::scoped_string_base &)has_get_string.get_string()); }
   //template < has_get_string HAS_GET_STRING >
   //inline const property & operator[](const HAS_GET_STRING & has_get_string) const { return payload((const ::scoped_string_base &)has_get_string.get_string()); }

   //template < has_as_string HAS_AS_STRING >
   //inline property & operator[](const HAS_AS_STRING & has_as_string) { return payload((const ::scoped_string_base &)has_as_string.as_string()); }
   //template < has_as_string HAS_AS_STRING >
   //inline const property & operator[](const HAS_AS_STRING & has_as_string) const { return payload((const ::scoped_string_base &)has_as_string.as_string()); }

   //inline property & operator[](const atom & atom) { return payload(atom); }
   //inline const property & operator[](const atom & atom) const { return payload(atom); }

   //inline property & operator[](const ::scoped_string & scopedstrName) { return payload(pszName); }
   //inline const property & operator[](const ::scoped_string & scopedstrName) const { return payload(pszName); }

   //inline property & operator[](const ::string & strName) { return payload(strName); }
   //inline const property & operator[](const ::string & strName) const { return payload(strName); }

   //inline property & operator[](::index iIndex) { return payload(iIndex); }
   //inline const property & operator[](::index iIndex) const { return payload(iIndex); }

   //inline property & operator[](const ::payload & payloadKey) { return payload(payloadKey); }
   //inline const property & operator[](const ::payload & payloadKey) const { return payload(payloadKey); }

//#ifdef OS64BIT
//
//   inline property & operator[](i32 iIndex) { return payload(iIndex); }
//   inline const property & operator[](i32 iIndex) const { return payload(iIndex); }
//
//#endif

   ::payload & topic(const atom & atom);

   ::payload_reference reference(const atom & atom) { return topic(atom); }

   ::payload & set(const atom & atom);

   property & at(index iId);
   ::payload at(index iId) const;

   property * find_value_ci(const ::payload & payload) const;
   property * find_value_ci(const ::scoped_string & scopedstr) const;

   property * find_payload(const ::payload & payload) const;
   property * find_payload(const ::scoped_string & scopedstr) const;

   property * str_find(const property & property) const;

   bool contains_value_ci(const ::payload & payload) const;
   bool contains_value_ci(const ::scoped_string & scopedstr) const;

   bool contains_payload(const ::payload & payload) const;
   bool contains_payload(const ::scoped_string & scopedstr) const;

   bool contains_value_ci(const ::payload & payload, ::count countMin = 1, ::count countMax = -1) const;
   bool contains_value_ci(const ::scoped_string & scopedstr, ::count countMin = 1, ::count countMax = -1) const;

   bool contains_payload(const ::payload & payload, ::count countMin = 1, ::count countMax = -1) const;
   bool contains_payload(const ::scoped_string & scopedstr, ::count countMin = 1, ::count countMax = -1) const;

   bool str_contains(const property_set & set) const;
   bool contains(const property_set & set) const;

   bool erase_first_value_ci(const ::payload & payload);
   bool erase_first_value_ci(const ::scoped_string & scopedstr);

   bool erase_first_value(const ::payload & payload);
   bool erase_first_value(const ::scoped_string & scopedstr);

   ::count erase_value_ci(const  ::payload & payload, ::count countMin = 0, ::count countMax = -1);
   ::count erase_value_ci(const ::scoped_string & scopedstr, ::count countMin = 0, ::count countMax = -1);

   ::count erase_value(const ::payload & payload, ::count countMin = 0, ::count countMax = -1);
   ::count erase_value(const ::scoped_string & scopedstr, ::count countMin = 0, ::count countMax = -1);

   bool has_property(atom idName) const;

   bool is_true(atom idName, bool bDefault = false) const;

   bool is_false(atom idName) const { auto p = find(idName); return !p || p->is_false(); }

   bool is_set_false(atom idName) const { auto p = find(idName); return !p || p->is_set_false(); }

   bool is_set_empty(::count countMinimum = 1) const;
   bool has_properties(::count countMinimum = 1) const;


   //inline auto names(index iStart = 0, index iEnd = -1) const { return name_iterator(iStart, iEnd, this); }


   inline property & set_at(const ::atom & atom, const ::payload & payload)
   {

      auto & property = get(atom);

      property = payload;

      return property;

   }

   bool get_string(string& strResult, const atom & idKey) const;

   ::payload get_value(const atom & idName);

   ::payload value(const atom & idName) const;

   ::payload value(const atom & idName, ::payload varDefault) const;

   bool payload_bool(const atom & atom, bool bDefault = false) const;
   ::string payload_string(const atom & atom, const ::string & strDefault = nullptr) const;
   ::file::path payload_file_path(const atom & atom, const ::file::path & pathDefault ={}) const;

   //template < typename TYPE >
   //inline void exchange(const ::atom & atom, TYPE & t)
   //{

   //   if (is_storing())
   //   {

   //      operator[](atom) = t;

   //   }
   //   else
   //   {

   //      t = operator[](atom);

   //   }

   //}

   //template < typename TYPE >
   //inline void exchange(const ::atom & atom, const TYPE & t)
   //{

   //   if (is_storing())
   //   {

   //      operator[](atom) = t;

   //   }
   //   else
   //   {

   //      throw ::exception(error_bad_argument);

   //   }

   //}

   //inline void exchange( const ::atom & atom, bool & b)
   //{

   //   if (is_storing())
   //   {

   //      if (b)
   //      {

   //         operator[](atom) = true;

   //      }
   //      else
   //      {

   //         erase_by_name(atom);

   //      }

   //   }
   //   else
   //   {

   //      b = is_true(atom);

   //   }

   //}

   ::count unset(const atom & idName);

   bool is_new(const atom & idName) const;

   bool is_null(const atom & idName) const;

   bool is_new_or_null(const atom & idName) const;

   
   using property_ptra::is_empty;

   bool is_empty(const atom & idName) const;


   //template < typename TYPE >
   //bool find(const ::atom & atom, TYPE & t)
   //{

   //   auto pproperty = find(atom);

   //   if (!pproperty)
   //   {

   //      return false;

   //   }

   //   t = (TYPE &) *pproperty;

   //   return true;

   //}


   void _008ParseCommandLine(const ::scoped_string & scopedstrCmdLine, ::payload & payloadFile);
   void _008ParseCommandFork(const ::scoped_string & scopedstrCmdLine, ::payload & payloadFile, string & strApp);
   void _008Parse(bool bApp, const ::scoped_string & scopedstrCmdLine, ::payload & payloadFile, string & strApp);
   void _008AddArgumentPairs(::string_array & straArguments);
   void _008AddArgumentOrFile(::payload & payloadFile, const ::string & strArgument);
   void _008AddArgument(const ::string & strArgument);
   void _008Add(const ::scoped_string & scopedstrKey, const ::scoped_string & scopedstrValue);

   void _008ParseCommandArguments(string_array & straArguments, ::payload & payloadFile, string & strApp);
   void _008ParseArguments(bool bApp, string_array & straArguments, ::payload & payloadFile, string & strApp);


   void clear();

   //virtual string eval(const ::string & str);

   //virtual string gen_eval(const ::string & str);

   //virtual string gen_string(const ::string & str);


   string evaluate(const ::string & str) const;

   bool get_evaluation(::string & str, const ::string & strExpression) const;


   void parse_ini(const ::string & strIni);
   //void parse_ini_file(const ::file::path& path);
   //void parse_ini_folder(const ::file::path& path);

   void parse_network_payload(const ::string & strNetworkPayload);
   void parse_network_payload(::ansi_range & range);
   void parse_network_arguments(const ::scoped_string & scopedstrUrl);
   void _parse_network_arguments(const ::scoped_string & scopedstrUrlQuery);
   void parse_network_headers(const ::scoped_string & scopedstrHeaders);


   string & get_network_arguments(string & str) const;
   string & get_network_payload(string & str, bool bNewLine = true) const;
   string get_network_arguments() const { string str; return get_network_arguments(str); }
   string get_network_payload() const { string str; return get_network_payload(str); }
   string get_command_line(const string_array & straKeys) const;
   string get_command_line() const;



   //virtual stream & write(::stream & stream) const override;
   //virtual stream & read(::stream & stream) override;


   virtual string implode(const ::scoped_string & scopedstrGlue) const;
   //::count get_count() const;


   property_set & operator = (const ::payload & payload);
   property_set & operator = (const property_set & set);
//   property_set & operator = (const pair_set_interface & set);
//   property_set & operator = (const str_str_interface & set);

   property_set & operator += (const property_set & set);
   property_set & operator |= (const property_set & set);


   property_set & append(const property_set & set);
   property_set & merge(const property_set & set);

   property_set & merge(const property & property);




   template < class T >
   pointer < T > cast(atom idName, T * pDefault = nullptr)
   {

      if (!has_property(idName))
         return pDefault;

      return operator[](idName).cast < T > (pDefault);

   }


   template < class T >
   pointer < T > cast(atom idName, T * pDefault = nullptr) const
   {

      return ((property_set *) this)->cast < T >(idName, pDefault);

   }


   void parse_environment_variable(const string_array & straEnvironment);


};


//CLASS_DECL_ACME void property_set_skip_network_payload(const char *& pszJson);
CLASS_DECL_ACME void property_set_skip_network_payload(::ansi_range & range);


//inline ::pointer<::handle::ini>operator ""_pini(const ::scoped_string & scopedstr, size_t s);


//inline ::handle::ini operator ""_ini(const ::scoped_string & scopedstr, size_t s);


//inline ::pointer<::property_set>localconfigini();






inline bool property_set::get_string(string & strResult, const atom & idKey) const
{

   auto property = operator[](idKey);

   if (property.is_empty())
   {

      return false;

   }

   strResult = property.as_string();

   return true;

}

