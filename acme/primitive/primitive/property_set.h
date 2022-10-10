#pragma once


// property set key is case insensitive
// PROPERTY_ARRAY Property set ordered
class CLASS_DECL_ACME property_set :
   public property_ptra
{
public:


   using ARRAY_BASE = typename property_ptra::ARRAY_BASE;


   using property_ptra::erase;


   __declare_iterator(name_iterator, &(*this->m_pelement)->m_atom);
   __declare_iterator(value_iterator, &(*this->m_pelement)->m_var);


   property_set() { }
   property_set(::std::initializer_list < ::payload > list);
   property_set(const property_set & set);
   property_set(property_set && set);
   virtual ~property_set();


   ::count erase_by_name(const atom & idName);
   ::count erase_by_name(string_array & straName);

   virtual ::matter * source_channel();

   inline ::payload operator()(const atom & atom, const ::payload & varDefault = ::error_not_found) const;

   string _001Replace(const ::string & str) const;

   inline string format(const ::string & str) const { return _001Replace(str); }

   inline property & payload(const atom & atom) { return get(atom); }
   inline const property & payload(const atom & atom) const { return *find(atom); }

   inline property & payload(const char * pszName) { return operator [](::atom(pszName)); }
   inline const property & payload(const char * pszName) const { return operator [](::atom(pszName)); }

   inline property & payload(const ::string & strName) { return operator [](::atom(strName)); }
   inline const property & payload(const ::string & strName) const { return operator [](::atom(strName)); }

   inline property & payload(::index iIndex) { return operator [](::atom(iIndex)); }
   inline const property & payload(::index iIndex) const { return operator [](::atom(iIndex)); }

   inline property & payload(const ::payload & payload) { return operator [](::atom(payload)); }
   inline const property & payload(const ::payload & payload) const { return operator [](::atom(payload)); }

#ifdef OS64BIT

   inline property & payload(i32 iIndex) { return operator []((::index) iIndex); }
   inline const property & payload(i32 iIndex) const { return operator []((::index) iIndex); }

#endif

   inline property & operator[](const atom & atom) { return payload(atom); }
   inline const property & operator[](const atom & atom) const { return payload(atom); }

   inline property & operator[](const char * pszName) { return payload(pszName); }
   inline const property & operator[](const char * pszName) const { return payload(pszName); }

   inline property & operator[](const ::string & strName) { return payload(strName); }
   inline const property & operator[](const ::string & strName) const { return payload(strName); }

   inline property & operator[](::index iIndex) { return payload(iIndex); }
   inline const property & operator[](::index iIndex) const { return payload(iIndex); }

   inline property & operator[](const ::payload & payloadKey) { return payload(payloadKey); }
   inline const property & operator[](const ::payload & payloadKey) const { return payload(payloadKey); }

#ifdef OS64BIT

   inline property & operator[](i32 iIndex) { return payload(iIndex); }
   inline const property & operator[](i32 iIndex) const { return payload(iIndex); }

#endif

   inline ::payload & topic(const atom & atom);

   inline ::payload_reference reference(const atom & atom) { return topic(atom); }

   ::payload & set(const atom & atom);

   property & at(index iId);
   ::payload at(index iId) const;

   property * find_value_ci(const ::payload & payload) const;
   property * find_value_ci(const char * psz) const;

   property * find_value(const ::payload & payload) const;
   property * find_value(const char * psz) const;

   property * str_find(const property & property) const;

   bool contains_value_ci(const ::payload & payload) const { return find_value_ci(payload) != nullptr; }
   bool contains_value_ci(const char * psz) const { return find_value_ci(psz) != nullptr; }

   bool contains_value(const ::payload & payload) const { return find_value(payload) != nullptr; }
   bool contains_value(const char * psz) const { return find_value(psz) != nullptr; }

   bool contains_value_ci(const ::payload & payload, ::count countMin = 1, ::count countMax = -1) const;
   bool contains_value_ci(const char * psz, ::count countMin = 1, ::count countMax = -1) const;

   bool contains_value(const ::payload & payload, ::count countMin = 1, ::count countMax = -1) const;
   bool contains_value(const char * psz, ::count countMin = 1, ::count countMax = -1) const;

   bool str_contains(const property_set & set) const;
   bool contains(const property_set & set) const;

   bool erase_first_value_ci(const ::payload & payload);
   bool erase_first_value_ci(const char * psz);

   bool erase_first_value(const ::payload & payload);
   bool erase_first_value(const char * psz);

   ::count erase_value_ci(const  ::payload & payload, ::count countMin = 0, ::count countMax = -1);
   ::count erase_value_ci(const char * psz, ::count countMin = 0, ::count countMax = -1);

   ::count erase_value(const ::payload & payload, ::count countMin = 0, ::count countMax = -1);
   ::count erase_value(const char * psz, ::count countMin = 0, ::count countMax = -1);

   bool has_property(atom idName) const;

   bool is_true(atom idName, bool bDefault = false) const;

   bool is_false(atom idName) const { auto p = find(idName); return !p || p->is_false(); }

   bool is_set_false(atom idName) const { auto p = find(idName); return !p || p->is_set_false(); }

   bool is_set_empty(::count countMinimum = 1) const;
   bool has_properties(::count countMinimum = 1) const;


   inline auto names(index iStart = 0, index iEnd = -1) const { return name_iterator(iStart, iEnd, this); }


   inline property & set_at(const ::atom & atom, const ::payload & payload)
   {

      auto & property = get(atom);

      property = payload;

      return property;

   }

   inline bool get_string(string& strResult, const atom & idKey) const;

   inline ::payload get_value(atom idName);

   inline ::payload value(atom idName) const;

   inline ::payload value(atom idName, ::payload varDefault) const;

   bool payload_bool(const atom & atom, bool bDefault = false) const;
   ::string payload_string(const atom & atom, const ::string & strDefault = nullptr) const;
   ::file::path payload_file_path(const atom & atom, const ::file::path & pathDefault ={}) const;

   template < typename TYPE >
   inline void exchange(const ::atom & atom, TYPE & t)
   {

      if (is_storing())
      {

         operator[](atom) = t;

      }
      else
      {

         t = operator[](atom);

      }

   }

   template < typename TYPE >
   inline void exchange(const ::atom & atom, const TYPE & t)
   {

      if (is_storing())
      {

         operator[](atom) = t;

      }
      else
      {

         throw ::exception(error_bad_argument);

      }

   }

   inline void exchange( const ::atom & atom, bool & b)
   {

      if (is_storing())
      {

         if (b)
         {

            operator[](atom) = true;

         }
         else
         {

            erase_by_name(atom);

         }

      }
      else
      {

         b = is_true(atom);

      }

   }

   ::count unset(const atom & idName);

   bool is_new(const atom & idName) const;

   bool is_null(const atom & idName) const;

   bool is_new_or_null(const atom & idName) const;

   
   using property_ptra::is_empty;

   bool is_empty(const atom & idName) const;

   ::index find_index(const ::atom & atom, ::index iStart = 0) const;

   property * find(const ::atom & atom) const;

   property & get(const ::atom & atom);


   inline property * find_property(const atom & atom) const { return find(atom); }
   inline property & get_property(const ::atom & atom) { return get(atom); }


   template < typename TYPE >
   bool find(const ::atom & atom, TYPE & t)
   {

      auto pproperty = find(atom);

      if (!pproperty)
      {

         return false;

      }

      t = (TYPE &) *pproperty;

      return true;

   }


   void _008ParseCommandLine(const char * pszCmdLine, ::payload & payloadFile);
   void _008ParseCommandFork(const char * pszCmdLine, ::payload & payloadFile, string & strApp);
   void _008Parse(bool bApp, const char * pszCmdLine, ::payload & payloadFile, string & strApp);
   void _008AddArgumentPairs(::string_array & straArguments);
   void _008AddArgumentOrFile(bool & bColon, ::payload & payloadFile, const ::string & strArgument);
   void _008AddArgument(const ::string & strArgument);
   void _008Add(const char * pszKey, const char * pszValue);

   void _008ParseCommandArguments(string_array & straArguments, ::payload & payloadFile, string & strApp);
   void _008ParseArguments(bool bApp, string_array & straArguments, ::payload & payloadFile, string & strApp);


   void clear();

   //virtual string eval(const ::string & str);

   //virtual string gen_eval(const ::string & str);

   //virtual string gen_string(const ::string & str);

   void parse_ini(const ::string & strIni);
   //void parse_ini_file(const ::file::path& path);
   //void parse_ini_folder(const ::file::path& path);

   void parse_network_payload(const ::string & strJson);
   void parse_network_payload(const char * & pszJson);
   void parse_network_payload(const char * & pszJson, const char * pszEnd);
   void parse_network_arguments(const char * pszUrl);
   void _parse_network_arguments(const char * pszUrlQuery);
   void parse_network_headers(const char * pszHeaders);


   string & get_network_arguments(string & str) const;
   string & get_network_payload(string & str, bool bNewLine = true) const;
   string get_network_arguments() const { string str; return get_network_arguments(str); }
   string get_network_payload() const { string str; return get_network_payload(str); }
   string get_command_line(const string_array & straKeys) const;
   string get_command_line() const;



   //virtual stream & write(::stream & stream) const override;
   //virtual stream & read(::stream & stream) override;


   virtual string implode(const char * pszGlue) const;
   //::count get_count() const;


   property_set & operator = (const ::payload & payload);
   property_set & operator = (const property_set & set);
//   property_set & operator = (const pair_set_interface & set);
//   property_set & operator = (const str_str_interface & set);

   property_set & operator += (const property_set & set);
   property_set & operator |= (const property_set & set);


   property & merge(const property& property) { return set_at(property.m_atom, property); }


   property_set & append(const property_set & set);
   property_set & merge(const property_set & set);


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


CLASS_DECL_ACME void property_set_skip_network_payload(const char *& pszJson);
CLASS_DECL_ACME void property_set_skip_network_payload(const char *& pszJson, const char * pszEnd);


// <3tbs!! - Talking... ~ and then end up creating a Handler that handles...
namespace handle
{
//
//
   class CLASS_DECL_ACME ini :
      public ::property_set
   {
   public:


      ini() {}
      ini(const ::string & str);
      ini(::file::file * pfile);
      ini(const ::property_set & set) : ::property_set(set) {}
      ini(::property_set && set) : ::property_set(::move(set)) {}
      ini(const ini & ini) : ::property_set(ini) {}
      ini(ini && ini) : property_set(::move(ini)) {}


      ini & operator =(const ini & ini) { if (this != &ini) ::property_set::operator=(ini); return *this; }
      ini & operator =(ini && ini) { if (this != &ini) ::property_set::operator=(::move(ini)); return *this; }


   };


   //class CLASS_DECL_ACME localini :
   //   public ini
   //{
   //public:

   //   localini(::matter * pobject);

   //};


} // namespace handle


//inline ::pointer<::handle::ini>operator ""_pini(const char * psz, size_t s);


//inline ::handle::ini operator ""_ini(const char * psz, size_t s);


//inline ::pointer<::property_set>localconfigini();



