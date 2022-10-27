#pragma once


//namespace aura
//{
//
//
//   namespace international
//   {
//
//
//      class locale_schema;
//
//
//   } // namespace international
//
//
//} // namespace aura
//
//
//
//namespace aura
//{
//
//
//   class str_context;
//
//
//   class CLASS_DECL_AURA str_schema :
//      public strid_map < string >
//   {
//   public:
//
//
//      atom m_atomSchema;
//
//
//      str_schema() { InitHashTable(4 * 1024 -1); };
//
//
//   };
//
//   class CLASS_DECL_AURA str_locale :
//      public strid_map < str_schema >
//   {
//   public:
//
//
//      atom       m_atomLang;
//
//      inline const str_schema * get_schema(const ::atom & idSchema) const
//      {
//         auto ppair = plookup(idSchema);
//         if (ppair == nullptr)
//            return nullptr;
//         return &ppair->element2();
//      }
//
//
//      str_locale() { InitHashTable(256 - 1); };
//
//
//   };
//
//
//   class CLASS_DECL_AURA str :
//      virtual public object
//   {
//   public:
//
//
//      str_schema *                     m_pschemaEn;
//      str_schema *                     m_pschemaStd;
//      strid_map < str_locale >         m_map;
//      
//
//      str();
//      virtual ~str();
//
//
//      inline const str_locale * get_locale(const ::atom & idLocale) const
//      {
//         
//         auto ppair = m_map.plookup(idLocale);
//
//         if (ppair == nullptr)
//         {
//
//            return nullptr;
//
//         }
//
//         return &ppair->element2();
//
//      }
//
//
//      virtual void initialize(::particle * pparticle) override;
//
//
//      inline auto& operator[](const ::atom& atom) { return m_map[atom]; }
//      inline auto& operator[](const ::atom& atom)const { return m_map[atom]; }
//
//      void set(const ::atom & atom, const ::atom & idLocale, const ::atom & idSchema, const ::string & psz);
//      string get(const str_context * pcontext, const ::atom & atom, bool bIdAsDefaultValue = true) const;
//      string get(const str_context * pcontext,const ::atom & atom,const ::atom & idLocale,const ::atom & idSchema,bool bIdAsDefaultValue = true) const;
//      void get(string_array & stra, const str_context * pcontext, const ::atom & atom) const;
//      void _get(string_array & stra, const str_context * pcontext, const ::atom & atom) const ;
//
//      bool load(const ::string & pszBaseDir);
//      bool load_uistr_file(const ::atom & idLocale, const ::atom & idSchema, const ::string & pszFile);
//
//      string body(const ::string & psz);
//
//      bool matches(const str_context * pcontext, const ::atom & atom, const ::string & psz) const;
//      bool begins(const str_context * pcontext, const ::string & psz, const ::atom & atom) const;
//      bool begins_eat(const str_context * pcontext, string & str, const ::atom & atom) const;
//
//
//   };
//
//
//
//   class CLASS_DECL_AURA str_context :
//      virtual public ::object
//   {
//   protected:
//
//      friend class str;
//      ::pointer<::text::international::locale_schema>    m_plocaleschema;
//
//
//      ::pointer<str>                                    m_pstr;
//
//      ::pointer<str_locale>                             m_plocale;
//
//      ::pointer<str_schema>                             m_pschema;
//      ::pointer<str_schema>                             m_pschemaLocale;
//      ::pointer<str_schema>                             m_pschemaSchemaEn;
//      ::pointer<str_schema>                             m_pschemaSchemaStd;
//
//
//
//      pointer_array < str_schema >                             m_schemaptra;
//
//
//   public:
//
//
//
//
//
//
//      textcontext();
//      virtual ~textcontext();
//
//      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
//      {
//         return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//      }
//
//      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS)
//      {
//         return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
//      }
//
//      inline void defer_ok(str * pstr)
//      {
//         if (pstr != m_pstr)
//         {
//            m_pstr = pstr;
//            prepare();
//         }
//      }
//
//      void set_str(str * pstr);
//
//      void prepare();
//
//
//      const comparable_array < atom > & locale_ex() const;
//
//      const comparable_array < atom > & schema_ex() const;
//
//
//      inline ::text::international::locale_schema & localeschema()
//      {
//         return *m_plocaleschema;
//      }
//
//      inline const ::text::international::locale_schema & localeschema() const
//      {
//         return *m_plocaleschema;
//      }
//
//      inline bool matches(const ::atom & atom, const ::string & psz) const
//      {
//
//         return m_pstr->matches(this, atom, psz);
//
//      }
//
//
//      inline bool begins(const ::atom & atom, const ::string & psz) const
//      {
//
//         return m_pstr->begins(this, __string(atom), psz);
//
//      }
//
//
//      inline bool begins_eat(string & str, const ::atom & atom) const
//      {
//
//         return m_pstr->begins_eat(this, str, atom);
//
//      }
//
//
//      inline void get(string_array & stra, const ::atom & atom) const
//      {
//
//         return m_pstr->get(stra, this, atom);
//
//
//      }
//
//
//      inline string get(const ::atom& atom) const
//      {
//         if (m_pstr == nullptr)
//            return atom.to_string();
//         return m_pstr->get(this, atom);
//
//      }
//
//      //virtual bool match(const regex * pregexp, string_array & stra, const ::string & psz, atom pszExp, atom pszRoot);
//
//      virtual bool match(string_array & stra, const ::string & psz, atom pszExp, atom pszRoot) const;
//
//
//   };
//
//
//
//
//} // namespace aura




