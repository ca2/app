#pragma once


// Include payload.h
// Don`t include this file directly


#include "acme/prototype/prototype/property.h"
#include "acme/prototype/collection/atom_array.h"
#include "acme/prototype/string/character_range.h"
//#include "payload_reference.h"


// ::property set key is case insensitive
// PROPERTY_ARRAY Property set ordered
class CLASS_DECL_ACME property_set :
   virtual public ::property_holder_array
{
public:


   //__declare_iterator(name_iterator, &(*this->m_pelement)->id());
   //__declare_iterator(value_iterator, &(*this->m_pelement)->m_var);


   property_set() {}
   property_set(::std::initializer_list < ::payload > list);
   property_set(const ::property_set & set);
   property_set(property_set && set);
   ~property_set() override;


   ::collection::count erase_by_name(const ::atom & atom);
   ::collection::count erase_by_name(string_array & straName);

   virtual ::particle * source_channel();

   //::payload operator()(const ::atom & atom, const ::payload & payloadDefault = ::error_not_found) const;

   string _001Replace(const ::string & str) const;

   inline string format(const ::string & str) const { return _001Replace(str); }


   string as_string(const ::scoped_string& scopedstrSeparator1, const ::scoped_string& scopedstrSeparator2);

   //::collection::index index_of(const ::atom & atom, ::collection::index iStart = 0) const;

   //::property* find_by_text(const ::scoped_string & scopedstr, ::collection::index iStart = 0) const;

   ::collection::index index_of(const ::atom& atom, ::collection::index iStart = 0) const;// { return atom.is_text() ? find_text_key((const ::scoped_string &)atom.m_str, iStart) : find_index(atom.m_i)
   ::property * lookup(const ::atom & atom, ::collection::index iStart = 0) const;// { return atom.is_text() ? find_text_key((const ::scoped_string &)atom.m_str, iStart) : find_index(atom.m_i)
   ::property & property(const ::atom & atom); // { return atom.is_text() ? get_text_key((const ::scoped_string &)atom.m_str, iStart) : get_index(atom.m_i); }
   const ::property& property(const ::atom& atom) const
   {

      return ((property_set*)this)->property(atom);

   }


   //::collection::index find(const ::atom_array& atoma) const;// { return atom.is_text() ? find_text_key((const ::scoped_string &)atom.m_str, iStart) : find_index(atom.m_i); }
   ::property * lookup(const ::atom_array & atoma) const;// { return atom.is_text() ? find_text_key((const ::scoped_string &)atom.m_str, iStart) : find_index(atom.m_i); }
   ::property & property(const ::atom_array & atoma); // { return atom.is_text() ? get_text_key((const ::scoped_string &)atom.m_str, iStart) : get_index(atom.m_i); }
   const ::property& property(const ::atom_array& atoma) const
   {

      return ((::property_set*)this)->property(atoma);

   }


   //::property * find_index(::iptr i) const;
   //::property & get_index(::iptr i);


   //::property * find_text_key(const scoped_string & scopedstr, ::collection::index iStart = 0) const;
   //::property & get_text_key(const scoped_string & scopedstr, ::collection::index iStart = 0);


   //inline ::property * find_property_index(::collection::index iIndex, ::collection::index iStart = 0) const { return find_index(iIndex); }
   //inline ::property & get_property_index(::collection::index iIndex, ::collection::index iStart = 0) { return get_index(iIndex); }


   //inline ::property * find_property_text_key(const scoped_string & scopedstr, ::collection::index iStart = 0) const { return find_text_key(scopedstr, iStart); }
   //inline ::property & get_property_text_key(const scoped_string & scopedstr, ::collection::index iStart = 0) { return get_text_key(scopedstr, iStart); }


   //inline ::property * payload_index(::iptr iIndex, ::collection::index iStart = 0) const { return find_property_index(iIndex); }
   //inline ::property & payload_index(::iptr iIndex, ::collection::index iStart = 0) { return get_property_index(iIndex); }


   //inline ::property * payload_text_key(const scoped_string & scopedstr, ::collection::index iStart = 0) const { return find_property_text_key(scopedstr, iStart); }
   //inline ::property & payload_text_key(const scoped_string & scopedstr, ::collection::index iStart = 0) { return get_property_text_key(scopedstr, iStart); }

   inline const ::property& operator[](const ::atom_array& atoma) const { return property(atoma); }
   inline const ::property& operator[](const ::atom& atom) const { return property(atom); }

   inline ::property & operator[](const ::atom_array & atoma) { return property(atoma); }
   inline ::property & operator[](const ::atom & atom) { return property(atom); }

   template < primitive_integral INTEGRAL >
   inline const ::property & property_at(INTEGRAL i) const { return *this->element_at(i); }
   template < primitive_integral INTEGRAL >
   inline ::property & property_at(INTEGRAL i) { return *this->element_at(i); }



   //template < character_range RANGE >
   //inline ::property & operator[](const RANGE & range) { return property(range); }
   //template < character_range RANGE >
   //inline const ::property & operator[](const RANGE & range) const { return property(range); }

   //template < has_get_string HAS_GET_STRING >
   //inline ::property & operator[](const HAS_GET_STRING & has_get_string) { return payload((const ::scoped_string_base &)has_get_string.get_string()); }
   //template < has_get_string HAS_GET_STRING >
   //inline const ::property & operator[](const HAS_GET_STRING & has_get_string) const { return payload((const ::scoped_string_base &)has_get_string.get_string()); }

   //template < has_as_string HAS_AS_STRING >
   //inline ::property & operator[](const HAS_AS_STRING & has_as_string) { return payload((const ::scoped_string_base &)has_as_string.as_string()); }
   //template < has_as_string HAS_AS_STRING >
   //inline const ::property & operator[](const HAS_AS_STRING & has_as_string) const { return payload((const ::scoped_string_base &)has_as_string.as_string()); }

   //inline ::property & operator[](const ::atom & atom) { return payload(atom); }
   //inline const ::property & operator[](const ::atom & atom) const { return payload(atom); }

   //inline ::property & operator[](const ::scoped_string & scopedstrName) { return payload(pszName); }
   //inline const ::property & operator[](const ::scoped_string & scopedstrName) const { return payload(pszName); }

   //inline ::property & operator[](const ::string & strName) { return payload(strName); }
   //inline const ::property & operator[](const ::string & strName) const { return payload(strName); }

   //inline ::property & operator[](::collection::index iIndex) { return payload(iIndex); }
   //inline const ::property & operator[](::collection::index iIndex) const { return payload(iIndex); }

   //inline ::property & operator[](const ::payload & payloadKey) { return payload(payloadKey); }
   //inline const ::property & operator[](const ::payload & payloadKey) const { return payload(payloadKey); }

//#ifdef OS64BIT
//
//   inline ::property & operator[](int iIndex) { return payload(iIndex); }
//   inline const ::property & operator[](int iIndex) const { return payload(iIndex); }
//
//#endif

   //::payload & topic(const ::atom & atom);

   //::payload_reference reference(const atom& atom); { return topic(atom); }

   ::payload_reference reference(const atom& atom);
   ::payload_reference reference(const atom_array & atom);

   //::payload & set(const ::atom & atom);

   //::property & at(::collection::index iId);
   //const ::property & at(::collection::index iId) const;

   ::collection::index index_of_case_insensitive_payload(const ::payload & payload, ::collection::index iStart = 0) const;
   ::collection::index index_of_case_insensitive_string(const ::scoped_string & scopedstr, ::collection::index iStart = 0) const;

   ::collection::index index_of_payload(const ::payload & payload, ::collection::index iStart = 0) const;
   ::collection::index index_of_string(const ::scoped_string & scopedstr, ::collection::index iStart = 0) const;

   //::property * str_find(const ::property & property) const;

   bool case_insensitive_contains_payload(const ::payload& payload, ::collection::index iStart = 0) const { return index_of_case_insensitive_payload(payload, iStart)>= 0; }
   bool case_insensitive_contains_string(const ::scoped_string & scopedstr, ::collection::index iStart = 0) const { return index_of_case_insensitive_string(scopedstr, iStart) >= 0; }

   bool contains_payload(const ::payload & payload, ::collection::index iStart = 0) const { return index_of_payload(payload, iStart) >= 0; }
   bool contains_string(const ::scoped_string & scopedstr, ::collection::index iStart = 0) const { return index_of_string(scopedstr, iStart) >= 0; }

   bool case_insensitive_contains_payload_count(const ::payload & payload, ::collection::count countMin = 1, ::collection::count countMax = -1) const;
   bool case_insensitive_contains_string_count(const ::scoped_string & scopedstr, ::collection::count countMin = 1, ::collection::count countMax = -1) const;

   bool contains_payload_count(const ::payload & payload, ::collection::count countMin = 1, ::collection::count countMax = -1) const;
   bool contains_string_count(const ::scoped_string & scopedstr, ::collection::count countMin = 1, ::collection::count countMax = -1) const;

   bool payload_contains(const ::property_set & set) const;
   bool string_contains(const ::property_set & set) const;
   bool contains_keys(const ::property_set & set) const;
   bool contains(const ::property_set & set) const;

   bool case_insensitive_erase_first_payload(const ::payload & payload, ::collection::index iStart = 0);
   bool case_insensitive_erase_first_string(const ::scoped_string & scopedstr, ::collection::index iStart = 0);

   bool erase_first_payload(const ::payload & payload, ::collection::index iStart = 0);
   bool erase_first_string(const ::scoped_string & scopedstr, ::collection::index iStart = 0);

   ::collection::count case_insensitive_erase_payload_count(const  ::payload & payload, ::collection::count countMin = 0, ::collection::count countMax = -1);
   ::collection::count case_insensitive_erase_string_count(const ::scoped_string & scopedstr, ::collection::count countMin = 0, ::collection::count countMax = -1);

   ::collection::count erase_payload_count(const ::payload & payload, ::collection::count countMin = 0, ::collection::count countMax = -1);
   ::collection::count erase_string_count(const ::scoped_string & scopedstr, ::collection::count countMin = 0, ::collection::count countMax = -1);

   bool has_property(const ::atom & atom) const;

   bool is_true(const ::atom & atom) const;

   bool is_true_or_empty(const ::atom & atom) const;

   bool is_false(const ::atom & atom) const { auto p = lookup(atom); return !p || p->is_false(); }

   bool is_set_false(const ::atom & atom) const { auto p = lookup(atom); return p && p->is_set_false(); }

   bool is_set_empty(::collection::count countMinimum = 1) const;

   bool has_properties(::collection::count countMinimum = 1) const;


   //inline auto names(::collection::index iStart = 0, ::collection::index iEnd = -1) const { return name_iterator(iStart, iEnd, this); }


   inline ::property & set_at(const ::atom & atom, const ::payload & payload)
   {

      auto & property = this->property(atom);

      property = payload;

      return property;

   }

   bool get_string(string& strResult, const ::atom & atom) const;

   ::payload get_payload(const ::atom & atom);

   const ::payload & payload(const ::atom & atom) const;

   ::payload & payload(const ::atom & atom, const ::payload & payloadDefault) const;

   bool get_bool(const ::atom & atom, bool bDefault = false) const;
   int get_int(const ::atom & atom, int iDefault = 0) const;
   unsigned int get_unsigned_int(const ::atom & atom, unsigned int uDefault = 0) const;
   ::string get_string(const ::atom & atom, const ::string & strDefault = nullptr) const;
   ::file::path get_file_path(const ::atom & atom, const ::file::path & pathDefault ={}) const;

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

   ::collection::count unset(const ::atom & atom);

   bool is_new(const ::atom & atom) const;

   bool is_null(const ::atom & atom) const;

   bool is_new_or_null(const ::atom & atom) const;

   
   //using property_ptra::is_empty;

   bool is_empty(const ::atom & atom) const;
   bool is_empty() const { return ::property_holder_array::is_empty(); }
   bool has_property() const { return this->has_element(); }
   ::collection::count property_count() const { return this->get_count(); }
   
   
   ::collection::index add_property(const ::atom & atom) { return this->add_item(new ::property(atom)); }
   ::property * add_property(const ::atom_array & atoma);
   ::collection::index add_property(const ::property & property) { return this->add_item(new ::property(property)); }


   inline const ::property & property_at(::collection::index nIndex) const { return *this->element_at(nIndex); }
   inline ::property & property_at(::collection::index nIndex) { return *this->element_at(nIndex); }

   inline ::collection::index erase_property_at(::collection::index iIndex) { return this->erase_at(iIndex); }

   inline ::collection::count erase_all_properties() { return this->erase_all(); }

   //auto begin() { return propertyptra().begin(); }
   //auto begin() const { return propertyptra().begin(); }
   //auto end() { return propertyptra().end(); }
   //auto end() const { return propertyptra().end(); }

   //auto is_end(property_arraytra::const_iterator iterator) const { return propertyptra().is_end(iterator); }

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
   ::string get_ini() const;
   ::string_array get_ini_lines() const;
   void parse_standard_configuration(const ::string & strStandardConfiguration);
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
   //::collection::count get_count() const;


   property_set & operator = (const ::payload & payload);
   property_set & operator = (const ::property_set & set);
//   property_set & operator = (const pair_set_interface & set);
//   property_set & operator = (const str_str_interface & set);

   property_set & operator += (const ::property_set & set);
   property_set & operator |= (const ::property_set & set);


   property_set & append(const ::property_set & set);
   property_set & merge(const ::property_set & set);

   property_set & merge(const ::property & property);




   template < primitive_subparticle T >
   T * cast(const ::atom & atom, T * pDefault = nullptr)
   {

      if (!has_property(atom))
      {

         return pDefault;

      }

      return operator[](atom).cast < T > (pDefault);

   }


   template < class T >
   T * cast(const ::atom & atom, T * pDefault = nullptr) const
   {

      return ((property_set *) this)->cast < T >(atom, pDefault);

   }


   void parse_environment_variable(const string_array & straEnvironment);


};


//CLASS_DECL_ACME void property_set_skip_network_payload(const char *& pszJson);
CLASS_DECL_ACME void property_set_skip_network_payload(::ansi_range & range);


//inline ::pointer<::handle::ini>operator ""_pini(const ::scoped_string & scopedstr, size_t s);


//inline ::handle::ini operator ""_ini(const ::scoped_string & scopedstr, size_t s);


//inline ::pointer<::property_set>localconfigini();


inline bool property_set::get_string(string & strResult, const ::atom & atom) const
{

   auto pproperty = lookup(atom);

   if (::is_null(pproperty))
   {

      return false;

   }

   strResult = pproperty->as_string();

   return true;

}


CLASS_DECL_ACME ::pointer < ::property_set > create_network_arguments_property_set(const ::scoped_string& scopedstrNetworkArguments);


