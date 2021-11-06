#pragma once


// property set key is case insensitive
// PROPERTY_ARRAY Property set ordered
class CLASS_DECL_ACME property_set :
   public property_ptra
{
public:


   using ARRAY_BASE = typename property_ptra::ARRAY_BASE;


   using property_ptra::erase;


   __declare_iterator(name_iterator, &(*this->m_pelement)->m_id);
   __declare_iterator(value_iterator, &(*this->m_pelement)->m_var);


   property_set() { }
   property_set(::std::initializer_list < ::payload > list);
   property_set(const property_set & set);
   property_set(property_set && set);
   virtual ~property_set();


   ::count erase_by_name(const id & idName);
   ::count erase_by_name(string_array & straName);

   virtual ::matter * source_channel();

   inline ::payload operator()(const id & id, const ::payload & varDefault = ::error_not_found) const;

   string _001Replace(const ::string & str) const;

   inline string format(const ::string & str) const { return _001Replace(str); }

   inline property & operator[](const id & id) { return get(id); }
   inline const property & operator[](const id & id) const { return *find(id); }

   inline property & operator[](const char * pszName) { return operator [](::id(pszName)); }
   inline const property & operator[](const char * pszName) const { return operator [](::id(pszName)); }

   inline property & operator[](const ::string & strName) { return operator [](::id(strName)); }
   inline const property & operator[](const ::string & strName) const { return operator [](::id(strName)); }

   inline property & operator[](::index iIndex) { return operator [](::id(iIndex)); }
   inline const property & operator[](::index iIndex) const { return operator [](::id(iIndex)); }

   inline property & operator[](const ::payload & payload) { return operator [](::id(payload)); }
   inline const property & operator[](const ::payload & payload) const { return operator [](::id(payload)); }

#ifdef OS64BIT

   inline property & operator[](i32 iIndex) { return operator []((::index) iIndex); }
   inline const property & operator[](i32 iIndex) const { return operator []((::index) iIndex); }

#endif

   inline ::payload & topic(const id & id);

   ::payload & set(const id & id);

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

   bool has_property(id idName) const;

   bool is_true(id idName, bool bDefault = false) const;

   bool is_false(id idName) const { auto p = find(idName); return !p || p->is_false(); }

   bool is_set_false(id idName) const { auto p = find(idName); return !p || p->is_set_false(); }

   bool is_set_empty(::count countMinimum = 1) const;
   bool has_properties(::count countMinimum = 1) const;


   inline auto names(index iStart = 0, index iEnd = -1) const { return name_iterator(iStart, iEnd, this); }


   inline property & set_at(const ::id & id, const ::payload & payload)
   {

      auto & property = get(id);

      property = payload;

      return property;

   }

   inline bool get_string(string& strResult, const id & idKey) const;

   inline ::payload get_value(id idName);

   inline ::payload value(id idName) const;

   inline ::payload value(id idName, ::payload varDefault) const;

   template < typename TYPE >
   inline void exchange(const ::id & id, TYPE & t)
   {

      if (is_storing())
      {

         operator[](id) = t;

      }
      else
      {

         t = operator[](id);

      }

   }

   template < typename TYPE >
   inline void exchange(const ::id & id, const TYPE & t)
   {

      if (is_storing())
      {

         operator[](id) = t;

      }
      else
      {

         __throw(error_invalid_argument);

      }

   }

   inline void exchange( const ::id & id, bool & b)
   {

      if (is_storing())
      {

         if (b)
         {

            operator[](id) = true;

         }
         else
         {

            erase_by_name(id);

         }

      }
      else
      {

         b = is_true(id);

      }

   }

   ::count unset(const id & idName);

   bool is_new(const id & idName) const;

   bool is_null(const id & idName) const;

   bool is_new_or_null(const id & idName) const;

   
   using property_ptra::is_empty;

   bool is_empty(const id & idName) const;

   ::index find_index(const ::id & id, ::index iStart = 0) const;

   property * find(const ::id & id) const;

   property & get(const ::id & id);


   inline property * find_property(const id & id) const { return find(id); }
   inline property & get_property(const ::id & id) { return get(id); }


   template < typename TYPE >
   bool find(const ::id & id, TYPE & t)
   {

      auto pproperty = find(id);

      if (!pproperty)
      {

         return false;

      }

      t = (TYPE &) payload_reference(*pproperty);

      return true;

   }


   void _008ParseCommandLine(const char * pszCmdLine, ::payload & payloadFile);
   void _008ParseCommandFork(const char * pszCmdLine, ::payload & payloadFile, string & strApp);
   void _008Parse(bool bApp, const char * pszCmdLine, ::payload & payloadFile, string & strApp);
   void _008Add(const char * pszKey, const char * pszValue);


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
   void parse_url_query(const char * pszUrl);
   void _parse_url_query(const char * pszUrlQuery);
   void parse_http_headers(const char * pszHeaders);


   string & get_http_post(string & str) const;
   string & get_network_payload(string & str, bool bNewLine = true) const;
   string get_http_post() const { string str; return get_http_post(str); }
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

   property_set & add(const property_set & set);
   property_set & merge(const property_set & set);


   template < class T >
   __pointer(T) cast(id idName, T * pDefault = nullptr)
   {

      if (!has_property(idName))
         return pDefault;

      return operator[](idName).cast < T > (pDefault);

   }


   template < class T >
   __pointer(T) cast(id idName, T * pDefault = nullptr) const
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


//inline __pointer(::handle::ini) operator ""_pini(const char * psz, size_t s);


//inline ::handle::ini operator ""_ini(const char * psz, size_t s);


//inline __pointer(::property_set) localconfigini();



