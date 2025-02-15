#pragma once


namespace simpledb
{


   class CLASS_DECL_CORE server:
      virtual public ::object
   {
      friend class result;
   public:


      string m_strLastError;
      long long m_iLastUsedTime;

      int       m_protocol;


      database(::particle * pparticle);
      virtual ~database();

      server(::particle * pparticle);
      virtual ~server();


      virtual bool open(const ::string & pszDatabase);
      virtual bool close();


      virtual bool sql(const ::string & pszQuery, ::payload & payload);



      virtual bool connect(
      const ::scoped_string & scopedstrHost,
      const ::scoped_string & scopedstrUser,
      const ::scoped_string & scopedstrPassword,
      const ::scoped_string & scopedstrDatabase,
      int iPort = 0,
      const ::scoped_string & scopedstrSocketName = nullptr,
      unsigned int uFlags = 0);

      virtual bool close();

      virtual bool initialize();

      virtual ::pointer<result>query(const ::string & pszSql);
      virtual ::payload query_item(const ::string & pszSql,::payload varDefault = false);
      virtual bool query_blob(memory_base & memory, const ::string & pszSql);
      virtual ::payload query_items(const ::string & pszSql);
      virtual ::payload query_row(const ::string & pszSql);
      virtual ::payload query_rows(const ::string & pszSql);


      virtual ::payload query_table_item(const ::string & table, const ::string & item, const ::string &where,::payload notfound = false);

      virtual ::payload get_agent(const ::string & pszTable, const ::string & pszEmail, const ::string & pszUser);

      virtual string escape(void * p,character_count iLine);
      virtual string escape(const ::string & psz);

      virtual ::payload get_insert_id();

      virtual string error1(const ::string & pszPrefix = nullptr);
      virtual void trace_error1(const ::string & pszPrefix = nullptr);

   };


} //   namespace simpledb



