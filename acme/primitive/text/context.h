#pragma once


namespace acme
{


   namespace international
   {


      class locale_schema;


   } // namespace international


} // namespace acme


namespace text
{


   class context;


   class CLASS_DECL_ACME schema :
      public strid_map < string >
   {
   public:


      ::id m_idSchema;


      schema() { InitHashTable(4 * 1024 -1); };


   };

   class CLASS_DECL_ACME locale :
      public strid_map < schema >
   {
   public:


      ::id       m_idLocale;

      inline const schema * get_schema(const ::id & idSchema) const
      {
         auto ppair = plookup(idSchema);
         if (ppair == nullptr)
            return nullptr;
         return &ppair->element2();
      }


      locale() { InitHashTable(256 - 1); };


   };


   class CLASS_DECL_ACME table :
      virtual public object
   {
   public:


      schema *                     m_pschemaEn;
      schema *                     m_pschemaStd;
      strid_map < locale >         m_map;
      

      table();
      virtual ~table();


      inline const locale * get_locale(const ::id & idLocale) const
      {
         
         auto ppair = m_map.plookup(idLocale);

         if (ppair == nullptr)
         {

            return nullptr;

         }

         return &ppair->element2();

      }


      virtual ::e_status initialize(::object * pobject) override;


      inline auto& operator[](const ::id& id) { return m_map[id]; }
      inline auto& operator[](const ::id& id)const { return m_map[id]; }

      void set(const ::id & id, const ::id & idLocale, const ::id & idSchema, const char * psz);
      string get(const context * pcontext, const ::id & id, bool bIdAsDefaultValue = true) const;
      string get(const context * pcontext,const ::id & id,const ::id & idLocale,const ::id & idSchema,bool bIdAsDefaultValue = true) const;
      void get(string_array & stra, const context * pcontext, const ::id & id) const;
      void _get(string_array & stra, const context * pcontext, const ::id & id) const ;

      bool load(const char * pszBaseDir);
      bool load_uistr_file(const ::id & idLocale, const ::id & idSchema, ::file::file * pfile);

      string body(const char * psz);

      bool matches(const context * pcontext, const ::id & id, const char * psz) const;
      bool begins(const context * pcontext, const char * psz, const ::id & id) const;
      bool begins_eat(const context * pcontext, string & str, const ::id & id) const;


   };



   class CLASS_DECL_ACME context :
      virtual public ::object
   {
   protected:


      friend class table;

      __pointer(::text::international::locale_schema)       m_plocaleschema;


      __pointer(table)                                      m_ptable;

      __pointer(locale)                                     m_plocale;

      __pointer(schema)                                     m_pschema;
      __pointer(schema)                                     m_pschemaLocale;
      __pointer(schema)                                     m_pschemaSchemaEn;
      __pointer(schema)                                     m_pschemaSchemaStd;



      __pointer_array(schema)                               m_schemaptra;


   public:


      context();
      virtual ~context();


      virtual i64 add_ref(OBJECT_REF_DEBUG_PARAMS)
      {

         return ::object::add_ref(OBJECT_REF_DEBUG_ARGS);

      }


      virtual i64 dec_ref(OBJECT_REF_DEBUG_PARAMS)
      {

         return ::object::dec_ref(OBJECT_REF_DEBUG_ARGS);

      }


      inline void defer_ok(table * ptable)
      {

         if (ptable != m_ptable)
         {

            m_ptable = ptable;

            prepare();

         }

      }


      void set_table(table* ptable);

      void prepare();


      const comparable_array < ::id > & locale_ex() const;

      const comparable_array < ::id > & schema_ex() const;


      inline ::text::international::locale_schema & localeschema()
      {
         
         return *m_plocaleschema;

      }


      inline const ::text::international::locale_schema & localeschema() const
      {

         return *m_plocaleschema;

      }


      inline bool matches(const ::id & id, const char * psz) const
      {

         return m_ptable->matches(this, id, psz);

      }


      inline bool begins(const ::id & id, const char * psz) const
      {

         return m_ptable->begins(this, __str(id), psz);

      }


      inline bool begins_eat(string & str, const ::id & id) const
      {

         return m_ptable->begins_eat(this, str, id);

      }


      inline void get(string_array & stra, const ::id & id) const
      {

         return m_ptable->get(stra, this, id);


      }


      inline string get(const ::id& id) const
      {
         if (m_ptable == nullptr)
            return id.to_string();
         return m_ptable->get(this, id);

      }

      //virtual bool match(const regex * pregexp, string_array & stra, const char * psz, id pszExp, id pszRoot);

      //virtual bool match(string_array & stra, const char * psz, ::id pszExp, ::id pszRoot) const;


   };


} // namespace acme



