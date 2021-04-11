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
//      id m_idSchema;
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
//      id       m_idLang;
//
//      inline const str_schema * get_schema(const ::id & idSchema) const
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
//      inline const str_locale * get_locale(const ::id & idLocale) const
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
//      virtual ::e_status initialize(::object * pobject) override;
//
//
//      inline auto& operator[](const ::id& id) { return m_map[id]; }
//      inline auto& operator[](const ::id& id)const { return m_map[id]; }
//
//      void set(const ::id & id, const ::id & idLocale, const ::id & idSchema, const char * psz);
//      string get(const str_context * pcontext, const ::id & id, bool bIdAsDefaultValue = true) const;
//      string get(const str_context * pcontext,const ::id & id,const ::id & idLocale,const ::id & idSchema,bool bIdAsDefaultValue = true) const;
//      void get(string_array & stra, const str_context * pcontext, const ::id & id) const;
//      void _get(string_array & stra, const str_context * pcontext, const ::id & id) const ;
//
//      bool load(const char * pszBaseDir);
//      bool load_uistr_file(const ::id & idLocale, const ::id & idSchema, const char * pszFile);
//
//      string body(const char * psz);
//
//      bool matches(const str_context * pcontext, const ::id & id, const char * psz) const;
//      bool begins(const str_context * pcontext, const char * psz, const ::id & id) const;
//      bool begins_eat(const str_context * pcontext, string & str, const ::id & id) const;
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
//      __pointer(::text::international::locale_schema)     m_plocaleschema;
//
//
//      __pointer(str)                                     m_pstr;
//
//      __pointer(str_locale)                              m_plocale;
//
//      __pointer(str_schema)                              m_pschema;
//      __pointer(str_schema)                              m_pschemaLocale;
//      __pointer(str_schema)                              m_pschemaSchemaEn;
//      __pointer(str_schema)                              m_pschemaSchemaStd;
//
//
//
//      __pointer_array(str_schema)                             m_schemaptra;
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
//      virtual i64 add_ref(OBJ_REF_DBG_PARAMS)
//      {
//         return ::object::add_ref(OBJ_REF_DBG_ARGS);
//      }
//
//      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS)
//      {
//         return ::object::dec_ref(OBJ_REF_DBG_ARGS);
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
//      const comparable_array < id > & locale_ex() const;
//
//      const comparable_array < id > & schema_ex() const;
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
//      inline bool matches(const ::id & id, const char * psz) const
//      {
//
//         return m_pstr->matches(this, id, psz);
//
//      }
//
//
//      inline bool begins(const ::id & id, const char * psz) const
//      {
//
//         return m_pstr->begins(this, __str(id), psz);
//
//      }
//
//
//      inline bool begins_eat(string & str, const ::id & id) const
//      {
//
//         return m_pstr->begins_eat(this, str, id);
//
//      }
//
//
//      inline void get(string_array & stra, const ::id & id) const
//      {
//
//         return m_pstr->get(stra, this, id);
//
//
//      }
//
//
//      inline string get(const ::id& id) const
//      {
//         if (m_pstr == nullptr)
//            return id.to_string();
//         return m_pstr->get(this, id);
//
//      }
//
//      //virtual bool match(const regex * pregexp, string_array & stra, const char * psz, id pszExp, id pszRoot);
//
//      virtual bool match(string_array & stra, const char * psz, id pszExp, id pszRoot) const;
//
//
//   };
//
//
//
//
//} // namespace aura




