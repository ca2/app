#pragma once


#include "acme/prototype/collection/atom_map.h"
//#include "acme/prototype/collection/pointer_array.h"
#include "acme/prototype/text/international_locale_schema.h"


namespace text
{


   class context;


   class schema :
      public atom_map < string >
   {
   public:


      ::atom m_atomSchema;


      schema() { InitHashTable(4 * 1024 -1); };


   };

   class CLASS_DECL_ACME locale :
      public atom_map < schema >
   {
   public:


      ::atom       m_atomLocale;

      inline const schema * get_schema(const ::atom & idSchema) const
      {
         
         auto p = plookup(idSchema);
         
         if (!p)
         {
            
            return nullptr;
            
         }
         
         return &p->element2();
         
      }


      locale() { InitHashTable(256 - 1); };


   };


   class CLASS_DECL_ACME table :
      virtual public ::particle
   {
   public:


      schema *                      m_pschemaEn;
      schema *                      m_pschemaStd;
      atom_map < locale >             m_map;
      

      table();
      ~table() override;


      inline const locale * get_locale(const ::atom & idLocale) const
      {
         
         auto p = m_map.plookup(idLocale);

         if (!p)
         {

            return nullptr;

         }

         return &p->element2();

      }


      virtual void initialize(::particle * pparticle) override;


      inline auto& operator[](const ::atom& atom) { return m_map[atom]; }
      inline auto& operator[](const ::atom& atom)const { return m_map[atom]; }

      void set(const ::atom & atom, const ::atom & idLocale, const ::atom & idSchema, const ::scoped_string & scopedstr);
      bool _get(::string & str, const ::text::context* pcontext, const ::atom& atom) const;
      string get(const ::text::context * pcontext, const ::atom & atom, bool bIdAsDefaultValue = true) const;
      string get(const ::text::context * pcontext,const ::atom & atom,const ::scoped_string & scopedstrLocale,const ::scoped_string & scopedstrSchema,bool bIdAsDefaultValue = true) const;
      void get(string_array_base & stra, const ::text::context * pcontext, const ::atom & atom) const;
      void _get(string_array_base & stra, const ::text::context * pcontext, const ::atom & atom) const ;

      bool load(const ::scoped_string & scopedstrBaseDir);
      bool load_uistr_file(const ::atom & idLocale, const ::atom & idSchema, ::file::file * pfile);

      string body(const ::scoped_string & scopedstr);

      bool matches(const ::text::context * pcontext, const ::atom & atom, const ::scoped_string & scopedstr) const;
      bool begins(const ::text::context * pcontext, const ::scoped_string & scopedstr, const ::atom & atom) const;
      bool begins_eat(const ::text::context * pcontext, string & str, const ::atom & atom) const;


   };


   class CLASS_DECL_ACME context :
      virtual public ::particle
   {
   protected:


      friend class table;

      ::pointer<::text::international::locale_schema>      m_plocaleschema;

      ::pointer<table>                                     m_ptable;

      ::pointer<locale>                                    m_plocale;

      ::pointer<schema>                                    m_pschema;
      ::pointer<schema>                                    m_pschemaLocale;
      ::pointer<schema>                                    m_pschemaSchemaEn;
      ::pointer<schema>                                    m_pschemaSchemaStd;



      pointer_array < schema >                               m_schemaptra;


   public:


      context();
      ~context() override;

#ifdef _DEBUG
      
      long long increment_reference_count() override
      {

         return ::particle::increment_reference_count();

      }


      long long decrement_reference_count() override
      {

         return ::particle::decrement_reference_count();

      }

#endif
      
      
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


      const string_array_base & locale_ex() const;

      const string_array_base & schema_ex() const;


      inline ::text::international::locale_schema * localeschema()
      {
         
         return m_plocaleschema;

      }


      inline const ::text::international::locale_schema & localeschema() const
      {

         return *m_plocaleschema;

      }


      inline bool matches(const ::atom & atom, const ::scoped_string & scopedstr) const
      {

         return m_ptable->matches(this, atom, scopedstr);

      }


      inline bool begins(const ::atom & atom, const ::scoped_string & scopedstr) const
      {

         return m_ptable->begins(this, scopedstr, atom);

      }


      inline bool begins_eat(string & str, const ::atom & atom) const
      {

         return m_ptable->begins_eat(this, str, atom);

      }


      inline void get(string_array_base & stra, const ::atom & atom) const
      {

         return m_ptable->get(stra, this, atom);


      }


      inline string get(const ::atom& atom) const
      {
         
         if (m_ptable == nullptr)
         {

            return atom.as_string();

         }

         return m_ptable->get(this, atom);

      }

      //virtual bool match(const regex * pregexp, string_array_base & stra, const ::scoped_string & scopedstr, atom pszExp, atom pszRoot);

      //virtual bool match(string_array_base & stra, const ::scoped_string & scopedstr, ::atom pszExp, ::atom pszRoot) const;


   };


} // namespace acme



